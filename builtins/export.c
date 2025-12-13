/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:26:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/13 21:20:49 by brmaria-         ###   ########.fr       */
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
		node->name = strndup(env_str);
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
	if (!((args[i] >= 'a' && args[i] <= 'z')
    		|| (args[i] >= 'A' && args[i] <= 'Z')
    		|| args[i] == '_'))
        return (0);
	i++;
	while (args[i] && args[i] != '=')
	{
		if (ft_isalnum(args[i]) || args[i] == '_' 
			|| (args[i] == '+' && args[i + 1] == '='))
			i++;
		else
			return (0);
	}
	return (1);
}

t_env	*get_value(t_env *env, char *name)
{
	    t_env *current = env;

    while (current)
    {
        if (ft_strncmp(current->name, name, ft_strlen(name) + 1) == 0)
			return (current);
		current = current->next;
    }
	return (NULL);
}

void set_value(char *str, t_env **env)
{
	char	*equal;
	char	*name;
	t_env	*target;
	int		is_append;
	t_env	*new;

	equal = ft_strchr(str, '=');
	is_append = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	if (equal && equal > str && equal[-1] == '+')
	{
		is_append = 1;
		name = ft_substr(str, 0, equal - str - 1);
	}
	else if (equal)
		name = ft_substr(str, 0, equal - str);
	else
		name = ft_strdup(str);
	target = get_value(*env, name);
	if (!target)
	{
		new = create_env_node(name);
		ft_envadd_back(env, new);
		free(name);
		return ;
	}
	if (equal)
	{
		if (is_append)
		{
			new->value = ft_strjoin(target->value, equal + 1);
			target->value = new->value;
		}
		else
			target->value = ft_strdup(equal + 1);
		free(target->value);
	}
	free(name);
}

/// @brief replicating export's behaviours
/// @param args the arguments received from terminal
/// @param env env's list
void	ft_export(char **args, t_shell *shell)
{
	int		i;
	t_env	*env;

	i = 0;
	env = shell->env;
	if (!args || !args[0])
	{
		while (env)
		{
			printf("declare -x ");
			printf("%s", env->name);
			if (env->value && env->value[0])
				printf("=");
			printf("\"%s\"", env->value);
			printf("\n");
			env = env->next;
		}
		shell->exit_status = 0;
		return ;
	}
	while (args[i])
	{
		if (!check_args(args[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			shell->exit_status = 1;
			return ;
		}
		set_value(args[i], &shell->env);
		i++;
	}
}
