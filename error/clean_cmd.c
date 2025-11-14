/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:29:21 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/14 19:12:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief cleans the t_cmd list
/// @param lst the pointer to the list
/// @param msg an error msg. NULL if not to print anything
void	ft_clean_cmd_lst(t_cmd *lst, char *msg)
{
	t_cmd	*current;

	if (!lst)
		return ;
	while (lst)
	{
		current = lst;
		lst = lst->next;
		if (!current)
			return ;
		if (current->redirs)
			ft_clean_redirs(current->redirs);
		if (current->cmd)
		{
			free(current->cmd);
			current->cmd = NULL;
		}
		if (current->args)
			ft_free_args(current->args);
		free(current);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
}

/// @brief cleans the redirections
/// @param redirs the list of redirections for an specific t_cmd
void	ft_clean_redirs(t_redir *redirs)
{
	t_redir	*current;

	if (!redirs)
		return ;
	while (redirs)
	{
		current = redirs;
		redirs = current->next;
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
	}
}
