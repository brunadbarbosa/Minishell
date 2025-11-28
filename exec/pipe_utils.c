/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:44:30 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/28 18:00:23 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_node_and_here(t_cmd *cmds, int *nd_cnt, int *hr_cnt);

/// @brief initializes the t_pipe struct
/// @param pipe the pipe struct to be initialized
/// @param cmds the list of commands from t_shell
/// @return 0 on sucess, greater on failure
int	init_pipe(t_pipe *pipe, t_cmd *cmds)
{
	int		node_counter;
	int		here_counter;
	int		i;

	pipe->pid_count = 0;
	pipe->prev_read_fd = -1;
	node_counter = 0;
	here_counter = 0;
	ft_node_and_here(cmds, &node_counter, &here_counter);
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

/// @brief counts the number of nodes and here_docs.
/// @param cmds the t_cmd list
/// @param nd_cnt node counter
/// @param hr_cnt here counter
static void	ft_node_and_here(t_cmd *cmds, int *nd_cnt, int *hr_cnt)
{
	t_cmd	*node;

	if (!cmds)
		return ;
	node = cmds;
	while (node)
	{
		*nd_cnt += 1;
		if (node->redirs && node->redirs->type == REDIR_HERE)
			*hr_cnt += 1;
		node = node->next;
	}
}

/// @brief frees the t_pipe struct after the pipe execution
/// @param pipe_st the struct allocated at ft_startproc
void	ft_freepipe_st(t_pipe *pipe_st)
{
	int	i;

	if (!pipe_st)
		return ;
	free(pipe_st->pids);
	i = 0;
	while (pipe_st->heredocs[i])
	{
		free(pipe_st->heredocs[i]);
		i++;
	}
	free(pipe_st->heredocs);
}
