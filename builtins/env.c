/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:32:06 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/13 20:30:25 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief find the last node of the list
/// @param lst env's list
/// @return the address of the last list's node
static t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/// @brief adding the variable created by export to the end of env's list
/// @param lst env's list
/// @param  new the new node
void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_envlast(*lst);
		last->next = new;
	}
}
 
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
