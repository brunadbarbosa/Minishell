/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:09 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/24 15:47:16 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe(int *pipefd, t_cmd *cmd)
{
	t_redir	*red;

	if (!pipefd || !cmd)
		return ;
	if (!cmd->redirs)
	{
		if (cmd->next)
		{
			if ((dup2(pipefd[1], STDOUT_FILENO) == -1))
			{
				ft_closepipe(pipefd[0], pipefd[1], "Failed to dup STDOUT");
				return ;
			}
		}
	}
	else
	{
		red = cmd->redirs;
		while (red)
		{
			
			red = red->next;
		}
	}
}
