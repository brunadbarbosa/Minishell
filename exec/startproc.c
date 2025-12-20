/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startproc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:47:40 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 15:34:13 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_wait(t_pipe *pipe, t_shell *shell);

static void	ft_handle_pipe(t_cmd *cmd, t_pipe *pipe_st)
{
	if (cmd->next && (pipe(pipe_st->pipefd) == -1))
		ft_freepipe_st(pipe_st);
}

/// @brief forks parent and child processes
/// @param lst the command list
/// @param pipe_st the struct with pipe information
/// @param shell the master struct
void	ft_fork(t_cmd *lst, t_pipe *pipe_st, t_shell *shell)
{
	t_cmd	*cmd;

	if (!lst || !pipe_st)
		return ;
	cmd = lst;
	while (cmd)
	{
		ft_handle_pipe(cmd, pipe_st);
		pipe_st->pids[pipe_st->pid_count] = fork();
		if (pipe_st->pids[pipe_st->pid_count] == -1)
			return (ft_freepipe_st(pipe_st));
		if (pipe_st->pids[pipe_st->pid_count] == 0)
		{
			setup_child_signals();
			ft_child(pipe_st, cmd, shell);
		}
		if (pipe_st->prev_read_fd != -1)
			close(pipe_st->prev_read_fd);
		if (cmd->next && (close(pipe_st->pipefd[1]), 1))
			pipe_st->prev_read_fd = pipe_st->pipefd[0];
		pipe_st->pid_count++;
		cmd = cmd->next;
	}
}

/// @brief starts the processes and waits on them
void	ft_startproc(t_shell *shell)
{
	t_pipe	pipe_st;

	if (!shell || !shell->cmds || !shell->env)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (init_pipe(&pipe_st, shell->cmds))
		return (ft_putstr_fd("Unable to initialize t_pipe pipe\n", 2));
	ft_fork(shell->cmds, &pipe_st, shell);
	if (pipe_st.prev_read_fd != -1)
		close(pipe_st.prev_read_fd);
	ft_wait(&pipe_st, shell);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_free_split(pipe_st.heredocs);
}

/// @brief waits on the child processes to be finished
static void	ft_wait(t_pipe *pipe, t_shell *shell)
{
	int	i;
	int	status;

	i = -1;
	while (++i < pipe->pid_count)
	{
		waitpid(pipe->pids[i], &status, 0);
		if (i == pipe->pid_count - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				shell->exit_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
			}
			else
				shell->exit_status = 1;
		}
	}
	free(pipe->pids);
}
