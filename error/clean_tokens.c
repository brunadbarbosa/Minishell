/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:17:25 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/10 19:49:06 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief cleans the list of t_token nodes
/// @param lst the list to be cleaned
void	ft_clean_tokens(t_token **lst, char *msg)
{
	t_token	*current;
	t_token	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current->next)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	free(current->value);
	free(current);
	*lst = NULL;
	if (msg)
		ft_putstr_fd(msg, 2);
}
