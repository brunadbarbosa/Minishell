/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:47:40 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/24 18:19:36 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		init_pipe(t_pipe *pipe, t_cmd *cmds);
static pid_t	ft_fork(t_cmd *cmd, t_env *env, t_shell *shell);
static void		ft_wait(t_pipe *pipe);

/// @brief starts the processes and waits on them
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

/// @brief initializes the t_pipe struct
/// @param pipe the pipe struct to be initialized
/// @param cmds the list of commands from t_shell
/// @return 0 on sucess, greater on failure
static int	init_pipe(t_pipe *pipe, t_cmd *cmds)
{
	int		node_counter;
	int		here_counter;
	t_cmd	*node;

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

/// @brief forks processes
/// @param cmd the list of commands
/// @param env the environment
/// @param shell the main struct
/// @return the pid of the child process	
static pid_t	ft_fork(t_cmd *cmd, t_env *env, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ft_pipe(cmd))
			ft_clean_shell(shell, "Failed at child\n");
		else
			ft_execve(cmd, env, shell);
	}
	return (pid);
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
			free(pipe->heredocs[i]); //build loop/function to unlink heredocs
			i++;
		}
		free(pipe->heredocs);
	}
}
