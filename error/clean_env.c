/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:30:14 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 18:36:19 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clean_env(t_env **env, char *msg)
{
	t_env	*current;

	if (!env || !*env)
		return ;
	while (*env)
	{
		current = *env;
		*env = (*env)->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		if (current->next)
			current->next = NULL;
		free(current);
	}
	*env = NULL;
	if (msg)
		ft_putstr_fd(msg, 2);
}
