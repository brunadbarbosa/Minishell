/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:47:40 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/21 15:32:06 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		init_pipe(t_pipe *pipe, t_cmd *cmds);
static pid_t	ft_process(t_cmd *cmd, t_env *env, t_shell *shell);
static void		ft_wait(t_pipe *pipe);
static void		ft_closepipe(int fd1, int fd2, char *str);

void	ft_exec(t_shell *shell)
{
	t_pipe	pipe;
	t_cmd	*cmd;

	if (!shell || !shell->cmds || !shell->env)
		return ;
	cmd = shell->cmds;
	if(init_pipe(&pipe, shell->cmds))
	{
		ft_putstr_fd("Unable to initialize t_pipe pipe\n", 2);
		return ;
	}
	while(cmd)
	{
		pipe.pids[pipe.pid_count] = ft_process(cmd, shell->env, shell);
		pipe.pid_count++;
		cmd = cmd->next;
	}
	ft_wait(&pipe);
}

static int	init_pipe(t_pipe *pipe, t_cmd *cmds)
{
	int		node_counter;
	int		here_counter;
	t_cmd	*node;

	pipe->fd_in = -1;
	pipe->fd_out = -1;
	pipe->pid_count = 0;
	node_counter = 0;
	node = cmds;
	while (node)
	{
		node = node->next;
		node_counter++;
		if (node->redirs && node->redirs->type == REDIR_HERE)
			here_counter++;
	}
	pipe->pids = malloc(sizeof(pid_t) * (node_counter - 1));
	if (!pipe->pids)
		return (1);
	pipe->heredocs = malloc(sizeof(char *) * here_counter + 1);
	if (!pipe->heredocs)
		return (free(pipe->pids), 2);
	return (0);
}

static pid_t	ft_process(t_cmd *cmd, t_env *env, t_shell *shell)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		perror("Failed to pipe in ft_process");
	pid = fork();
	if (pid == -1)
		ft_closepipe(pipefd[0], pipefd[1], "Failed to fork in ft_process");
	else if (pid == 0)
	{
		if((dup2(pipefd[1], STDOUT_FILENO)) == -1)
			perror("dup2 failed in child process");
		ft_closepipe(pipefd[0], pipefd[1], NULL);
		ft_execute(cmd, env, pipefd);
	}
	else
	{
		if ((dup2(pipefd[0], STDIN_FILENO)) == -1)
			perror("dup2 failed in parent process");
		ft_closepipe(pipefd[0], pipefd[1], NULL);
	}
	return (pid);
}

static void	ft_wait(t_pipe *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->pid_count)
	{
		waitpid(pipe->pids[i], NULL, 0);
		i++;
	}
	free(pipe->pids);
	if (pipe->heredocs)
	{
		i = 0;
		while (pipe->heredocs[i])
		{
			free(pipe->heredocs[i]);
			i++;
		}
		free(pipe->heredocs);
	}
}

static void	ft_closepipe(int fd1, int fd2, char *str)
{
	if (fd1 >= 0)
	{
		close(fd1);
		fd1 = -1;
	}
	if (fd2 >= 0)
	{
		close(fd2);
		fd2 = -1;
	}
	if (str)
		ft_putstr_fd(str, 2);
}
