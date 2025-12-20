/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:17:25 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 18:36:14 by brmaria-         ###   ########.fr       */
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
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
	if (msg)
		ft_putstr_fd(msg, 2);
}
