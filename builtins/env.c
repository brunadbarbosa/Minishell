/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:32:06 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/14 16:34:36 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief Will print all env's list
/// @param env to be printed
void	ft_env(t_env *env)
{
	while (env)
	{
		if (!env->value)
			return ;
		if (env->value && env->value[0])
		{
			printf("%s=", env->name);
			printf("%s", env->value);
			printf("\n");
		}
		env = env->next;
	}
}
