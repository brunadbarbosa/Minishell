/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:09 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/24 16:45:44 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipe(t_cmd *cmdlst)
{
	t_cmd	*cmd;

	if (!cmdlst)
		return ;
	cmd = cmdlst;
	while (cmd)
	{
		if (cmd->redirs)
		{
			while (cmd->redirs)
			{
				if (ft_redcmd(cmd->redirs->type, cmd->redirs->fd));
					return (1) ;
				cmd->redirs = cmd->redirs->next;
			}
		}
		else if (cmd->next)
			//regular pipe
		cmd = cmd->next;
	}
	return (0);
}

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
	}
	else if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		if ((dup2(fd, STDOUT_FILENO)) == -1)
		{
			close(fd);
			ft_putstr_fd("Failed stdout at ft_redcmd\n", 2);
			return (2);
		}
	}
	return (0);
}
