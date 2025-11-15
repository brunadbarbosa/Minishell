/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:26:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/15 17:49:04 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

int	check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if ((args[i][j] >= 'a' && args[i][j] <= 'z') || (args[i][j] >= 'A' && args[i][j] <= 'Z') || args[i][j] == '_')
				j++;
			else
				return (0);
		}
		i++;
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
	
	if (!check_args(args))
	{
		printf("export: '%s': not a valid identifier\n", *args);
		return ;
	}
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
