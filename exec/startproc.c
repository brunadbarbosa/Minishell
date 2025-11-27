/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startproc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:47:40 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/27 18:21:51 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		init_pipe(t_pipe *pipe, t_cmd *cmds);
static void		ft_wait(t_pipe *pipe);
static int		ft_redcmd(int type, int fd);

/// @brief starts the processes and waits on them
void	ft_startproc(t_shell *shell)
{
	t_pipe	pipest;
	t_cmd	*cmd;
	int		pipefd[2];
	int		prev_read_fd;

	if (!shell || !shell->cmds || !shell->env)
		return ;
	if(init_pipe(&pipest, shell->cmds))
		return (ft_putstr_fd("Unable to initialize t_pipe pipe\n", 2));
	cmd = shell->cmds;
	prev_read_fd = -1;
	while(cmd)
	{
		if (cmd->next && (pipe(pipefd) == -1))
			return ;
		pipest.pids[pipest.pid_count] = fork();
		if (pipest.pids[pipest.pid_count] == 0)
		{
			if (prev_read_fd != -1)
			{
				dup2(prev_read_fd, STDIN_FILENO);
				close(prev_read_fd);
			}
			if (cmd->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			while (cmd->redirs)
			{
				if (ft_redcmd(cmd->redirs->type, cmd->redirs->fd))
					return ;
				cmd->redirs = cmd->redirs->next;
			}
			ft_execute(cmd, shell->env, shell);
			exit (1);
		}
		if (prev_read_fd != -1)
			close(prev_read_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_read_fd = pipefd[0];
		}
		pipest.pid_count++;
		cmd = cmd->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	ft_wait(&pipest);
}

/// @brief initializes the t_pipe struct
/// @param pipe the pipe struct to be initialized
/// @param cmds the list of commands from t_shell
/// @return 0 on sucess, greater on failure
static int	init_pipe(t_pipe *pipe, t_cmd *cmds)
{
	int		node_counter;
	int		here_counter;
	t_cmd	*node;
	int		i;

	pipe->pid_count = 0;
	node_counter = 0;
	here_counter = 0;
	node = cmds;
	while (node)
	{
		node_counter++;
		if (node->redirs && node->redirs->type == REDIR_HERE)
			here_counter++;
		node = node->next;
	}
	pipe->pids = malloc(sizeof(pid_t) * node_counter);
	if (!pipe->pids)
		return (1);
	pipe->heredocs = malloc(sizeof(char *) * (here_counter + 1));
	if (!pipe->heredocs)
		return (free(pipe->pids), 2);
	i = 0;
	while (i <= here_counter)
		pipe->heredocs[i++] = NULL;
	return (0);
}

/// @brief waits on the child processes to be finished
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
			unlink(pipe->heredocs[i]);
			free(pipe->heredocs[i]);
			i++;
		}
		free(pipe->heredocs);
	}
}

/// @brief redirects command to its infile and outfile
/// @param type the redirection type
/// @param fd the file descriptor of the redirection file
/// @return 0 on success, greater then 0 on failure
static int	ft_redcmd(int type, int fd)
{
	if (type == REDIR_IN || type == REDIR_HERE)
	{
		if ((dup2(fd, STDIN_FILENO)) == -1)
		{
			close(fd);
			ft_putstr_fd("Failed stdin at ft_redcmd\n", 2);
			return (1);
		}
		close(fd);
	}
	else if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		if ((dup2(fd, STDOUT_FILENO)) == -1)
		{
			close(fd);
			ft_putstr_fd("Failed stdout at ft_redcmd\n", 2);
			return (2);
		}
		close(fd);
	}
	return (0);
}
