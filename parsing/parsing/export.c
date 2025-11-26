/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:26:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/26 17:38:41 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env *env);

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

int	check_args(char *args)
{
	int	i;
	
	i = 0;
	while (args[i])
	{
		if ((args[i] >= 'a' && args[i] <= 'z') || (args[i] >= 'A' && args[i] <= 'Z') || args[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

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
static void	ft_envadd_back(t_env *lst, t_env *new)
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
/// @brief replicating export's behaviours
/// @param args the arguments received from terminal
/// @param env env's list
void	ft_export(char **args, t_shell *shell)
{
	int	i;
	t_env	*new;
	t_env	*env;

	i = 0;
	env = shell->env;	
	if (!args || !args[1])
	{
		while (env)
		{
			printf("declare -x ");
			printf("%s", env->name);
			if (env->value && env->value[0])
				printf("=");
			printf("%s", env->value);	
			printf("\n");
			env = env->next;
		}
		return ;
	}
	while (args[i])
	{
		printf("entrei aqui!");
		if (!check_args(args[i]))
		{
			printf("export: '%s': not a valid identifier\n", *args);
			return ;
		}
		new = create_env_node(args[i]);
		ft_envadd_back(env, new);
		i++;
	}
	if (args[2])
	{
		ft_export(NULL, shell);
		ft_env(env);
	}
}
