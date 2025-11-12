/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:59:27 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/12 15:56:33 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// // função auxiliar pra criar um nó
// static t_env	*create_env_node(const char *env_str)
// {
// 	t_env	*node;
// 	char	*equal;

// 	node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);

// 	equal = strchr(env_str, '=');

// 	if (equal)
// 	{
// 		node->name = strndup(env_str, equal - env_str);
// 		node->value = strdup(equal + 1); // valor completo após o '='
// 	}
// 	else
// 	{
// 		node->name = strdup(env_str);
// 		node->value = strdup("");
// 	}
// 	node->next = NULL;
// 	return (node);
// }

// // função principal para copiar o ambiente
// t_env	*init_env_list(char **envp)
// {
// 	t_env	*head = NULL;
// 	t_env	*tail = NULL;
// 	t_env	*new_node;
// 	int		i = 0;

// 	while (envp[i])
// 	{
// 		new_node = create_env_node(envp[i]);
// 		if (!new_node)
// 			return (NULL); // (depois podes tratar leaks)
// 		if (!head)
// 			head = new_node;
// 		else
// 			tail->next = new_node;
// 		tail = new_node;
// 		i++;
// 	}
// 	return (head);
// }

void	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=", env->name);
		printf("%s", env->value);	
		printf("\n");
		env = env->next;
	}
}

// int	main(int argc, char **argv, char **envp)
// {	
// 	t_env	*env;
// 	(void)argc;
// 	(void)argv;
// 	env = init_env_list(envp);
// 	ft_env(env);
// 	return (0);
// }