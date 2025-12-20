/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:29:21 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 18:36:22 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief cleans the t_cmd list
/// @param lst the pointer to the list
/// @param msg an error msg. NULL if not to print anything
void	ft_clean_cmd_lst(t_cmd **lst, char *msg)
{
	t_cmd	*current;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		current = *lst;
		*lst = (*lst)->next;
		if (current->redirs)
			ft_clean_redirs(&current->redirs);
		if (current->cmd)
		{
			free(current->cmd);
			current->cmd = NULL;
		}
		if (current->args)
			ft_free_args(current->args);
		free(current);
		current = NULL;
	}
	*lst = NULL;
	if (msg)
		ft_putstr_fd(msg, 2);
}

/// @brief cleans the redirections
/// @param redirs the list of redirections for an specific t_cmd
void	ft_clean_redirs(t_redir **redirs)
{
	t_redir	*current;

	if (!redirs || !*redirs)
		return ;
	while (*redirs)
	{
		current = *redirs;
		*redirs = (*redirs)->next;
		if (current->file)
		{
			free(current->file);
			current->file = NULL;
		}
		if (current->fd != -1)
		{
			close(current->fd);
			current->fd = -1;
		}
		free(current);
		current = NULL;
	}
	*redirs = NULL;
}
