/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:26:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/20 18:36:36 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_name(char *str, int *is_append)
{
	char	*equal;

	*is_append = 0;
	equal = ft_strchr(str, '=');
	if (!equal)
		return (ft_strdup(str));
	if (equal > str && equal[-1] == '+')
	{
		*is_append = 1;
		return (ft_substr(str, 0, equal - str - 1));
	}
	return (ft_substr(str, 0, equal - str));
}

void	update_value(t_env *target, char *str, int is_append)
{
	char	*equal;
	char	*old;

	equal = ft_strchr(str, '=');
	if (!equal)
		return ;
	old = target->value;
	if (is_append)
		target->value = ft_strjoin(old, equal + 1);
	else
		target->value = ft_strdup(equal + 1);
	free(old);
}

void	set_value(char *str, t_env *env)
{
	char	*name;
	t_env	*target;
	int		is_append;
	t_env	*new;

	name = extract_name(str, &is_append);
	if (!name)
		return ;
	target = get_value(env, name);
	if (!target)
	{
		new = create_env_node(name);
		if (new)
			ft_envadd_back(env, new);
	}
	else
		update_value(target, str, is_append);
	free(name);
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("declare -x ");
		printf("%s", env->name);
		if (env->value && env->value[0])
		{
			printf("=");
			printf("\"%s\"", env->value);
		}
		printf("\n");
		env = env->next;
	}
}

/// @brief replicating export's behaviours
/// @param args the arguments received from terminal
/// @param env env's list
void	ft_export(char **args, t_shell *shell, t_env *env)
{
	int		i;

	i = -1;
	if (!args || !args[0])
	{
		print_env(env);
		shell->exit_status = 0;
		return ;
	}
	while (args[++i])
	{
		if (!check_args(args[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			shell->exit_status = 1;
			return ;
		}
		set_value(args[i], env);
	}
}
