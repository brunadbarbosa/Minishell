/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:52:15 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/24 14:50:41 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_args(char *args);

void	remove_env(t_env **env, char *name)
{
	    t_env *current = *env;
    	t_env *prev = NULL;

    while (current)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (prev == NULL)
                *env = current->next;
            else
                prev->next = current->next;

            free(current->name);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void	ft_unset(char **args, t_env **env)
{
	int	i;

	i = 0;

	while (args[i])
	{
		if (!check_args(args[i]))
			printf("unset: `%s': not a valid identifier\n", args[i]);
		else
			remove_env(env, args[i]);
		i++;
	}
}