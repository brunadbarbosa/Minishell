/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:26:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/12 17:05:24 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief generates the command list from the token list
void	ft_parser(t_shell *shell)
{
	if (!shell)
		return ;
	ft_cmd_lst_init(&shell);
	ft_cmd_lst(&shell);
}

void	ft_cmd_lst_init(t_shell *shell)
{
	if (!shell)
		return ;
	shell->cmds = malloc(sizeof(t_cmd));
	if (!shell->cmds)
		ft_clean_shell(&shell, "Failed allocating t_cmd\n");
	shell->cmds->cmd = NULL;
	shell->cmds->args = NULL;
	shell->cmds->next = NULL;
	shell->cmds->redirs = NULL;
}
