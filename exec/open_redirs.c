/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:20 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/10 14:45:09 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_redir(t_redir *red, t_shell *shell);

int	ft_openredirs(t_cmd *cmdlst, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*red;

	if (!cmdlst)
		return (2);
	cmd = cmdlst;
	while (cmd)
	{
		red = cmd->redirs;
		if (red)
		{
			while (red)
			{
				if (get_redir(red, shell))
					return (1);
				red = red->next;
			}
		}
		cmd = cmd->next;
	}
	return (0);
}

int	get_redir(t_redir *red, t_shell *shell)
{
	(void)shell;
	if (red->type == REDIR_APPEND)
		red->fd = open(red->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (red->type == REDIR_IN)
		red->fd = open(red->file, O_RDONLY, 0644);
	else if (red->type == REDIR_OUT)
		red->fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red->type == REDIR_HERE)
		ft_printf("Heredoc!");
	if (red->fd < 0)
	{
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}
