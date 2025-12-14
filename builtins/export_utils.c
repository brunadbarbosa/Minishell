/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:18:17 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/14 14:03:46 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		node->name = ft_substr(env_str, 0, equal - env_str);
		node->value = ft_strdup(equal + 1);
	}
	else
	{
		node->name = ft_strdup(env_str);
		node->value = ft_strdup("");
	}
	node->next = NULL;
	return (node);
}

int	check_args(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[i]) && args[i] != '_')
		return (0);
	i++;
	while (args[i] && args[i] != '=')
	{
		if (!ft_isalnum(args[i]) && args[i] != '_'
			&& !(args[i] == '+' && args[i + 1] == '='))
			return (0);
		i++;
	}
	return (1);
}

t_env	*get_value(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/// @brief find the last node of the list
/// @param lst env's list
/// @return the address of the last list's node
t_env	*ft_envlast(t_env *lst)
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
void	ft_envadd_back(t_env *lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (lst == NULL)
		lst = new;
	else
	{
		last = ft_envlast(lst);
		last->next = new;
	}
}
