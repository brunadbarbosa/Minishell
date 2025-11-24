/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:20 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/24 16:05:30 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_redir(t_redir *red);

void	ft_openredirs(t_cmd *cmdlst)
{
	t_cmd	*cmd;
	t_redir	*red;

	if (!cmdlst)
		return ;
	cmd = cmdlst;
	while (cmd)
	{
		red = cmd->redirs;
		if (red)
		{
			while (red)
			{
				get_redir(red);
				red = red->next;
			}
		}
		cmd = cmd->next;
	}
}

static void	get_redir(t_redir *red)
{
	if (red->type == REDIR_APPEND)
		red->fd = open(red->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (red->type == REDIR_IN)
		red->fd = open(red->file, O_RDONLY, 0644);
	else if (red->type == REDIR_OUT)
		red->fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red->type == REDIR_HERE)
		ft_printf("Heredoc!");
	return ;
}
