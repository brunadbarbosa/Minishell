/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startproc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:47:40 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/13 15:55:58 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_wait(t_pipe *pipe, t_shell *shell);

/// @brief starts the processes and waits on them
void	ft_startproc(t_shell *shell)
{
	t_pipe	pipe_st;

	if (!shell || !shell->cmds || !shell->env)
		return ;
	if (init_pipe(&pipe_st, shell->cmds))
		return (ft_putstr_fd("Unable to initialize t_pipe pipe\n", 2));
	ft_fork(shell->cmds, &pipe_st, shell);
	if (pipe_st.prev_read_fd != -1)
		close(pipe_st.prev_read_fd);
	ft_wait(&pipe_st, shell);
}

/// @brief waits on the child processes to be finished
static void	ft_wait(t_pipe *pipe, t_shell *shell)
{
	int	i;
	int	status;
	int	sig;

	i = 0;
	while (i < pipe->pid_count)
	{
		waitpid(pipe->pids[i], &status, 0);
		if (i == pipe->pid_count - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				shell->exit_status = 128 + sig;
				if (sig == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
				else if (sig == SIGINT)
					write(1, "\n", 1);
			}
			else
				shell->exit_status = 1;
		}
		i++;
	}
	free(pipe->pids);
}
