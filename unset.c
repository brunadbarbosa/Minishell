/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:52:15 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/16 17:33:16 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_env(t_env *env, char *args)
{
	
}

void	ft_unset(char **args, t_env *env)
{
	int	i;

	i = 0;

	if (!args[1])
		return ;
	while (args[i])
	{
		if (!check_args(args[i]))
			printf("unset: `%s': not a valid identifier\n", args[i]);
		else
			remove_env(env, args[i]);
		i++;
	}
}