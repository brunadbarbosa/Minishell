/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:30:14 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/12 19:38:30 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clean_env(t_env *env, char *msg)
{
	t_env	*current;

	if (!env)
		return ;
	while(env)
	{
		current = env;
		if (current->name)
		{
			free(current->name);
			current->name = NULL;
		}
		if (current->value)
			ft_free_args(&current->value);
		if (env->next)
			env = env->next;
		free(current);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
}
