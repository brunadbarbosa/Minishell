/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:30:22 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/15 18:46:12 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief cleans the t_shell super structure
/// @param shell the reference to the t_shell structure
/// @param msg str to be printed in case of error
void	ft_clean_shell(t_shell *shell, char *msg)
{
	if (!shell)
		return ;
	if (shell->cmds)
	{
		ft_clean_cmd_lst(&shell->cmds, msg);
		shell->cmds = NULL;
	}
	if (shell->env)
	{
		ft_clean_env(&shell->env, msg);
		shell->env = NULL;
	}
	if (shell->tokens)
	{
		ft_clean_tokens(&shell->tokens, msg);
		shell->tokens = NULL;
	}
	if (shell->heredoc)
		ft_free_args(shell->heredoc);
}
