/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:26:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/20 16:06:20 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

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
static void	ft_envadd_back(t_env **lst, t_env *new)
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
/// @brief replicating export's behaviours
/// @param args the arguments received from terminal
/// @param env env's list
void	ft_export(char **args, t_env *env)
{
	int	i;
	t_env	*new;

	i = 0;
	
	if (!args || !args[0])
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
		if (!check_args(args[i]))
		{
			printf("export: '%s': not a valid identifier\n", *args);
			return ;
		}
		new = create_env_node(args[i]);
		ft_envadd_back(&env, new);
		i++;
	}
	if (args[2])
	{
		ft_export(NULL, env);
		ft_env(env);
	}
}
