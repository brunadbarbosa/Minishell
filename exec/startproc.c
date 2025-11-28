/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startproc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:47:40 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/28 18:31:39 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_wait(t_pipe *pipe);

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
	ft_wait(&pipe_st);
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
