/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:59:27 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/24 15:01:29 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/// @brief this function will create a new node
/// @param env_str the argument that I'll use to fill env node
/// @return new node
t_env	*create_env_node(const char *env_str)
{
	t_env	*node;
	char	*equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);

	equal = strchr(env_str, '=');

	if (equal)
	{
		node->name = strndup(env_str, equal - env_str);
		node->value = strdup(equal + 1);
	}
	else
	{
		node->name = strdup(env_str);
		node->value = strdup("");
	}
	node->next = NULL;
	return (node);
}

/// @brief creating the env list
/// @param envp to be copied
/// @return the list
t_env	*init_env_list(char **envp)
{
	t_env	*head = NULL;
	t_env	*tail = NULL;
	t_env	*new_node;
	int		i = 0;

	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (head);
}
/// @brief Will print all env's list
/// @param env to be printed
void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->value[0])
		{
			printf("%s=", env->name);
			printf("%s", env->value);	
			printf("\n");
		}
			env = env->next;
	}
}
