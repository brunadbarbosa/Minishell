/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:52:15 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/10 11:22:15 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_unset(char **args, t_shell *shell)
{
	int	i;

	i = 0;

	while (args[i])
	{
		remove_env(&shell->env, args[i]);
		i++;
	}
	shell->exit_status = 0;
}