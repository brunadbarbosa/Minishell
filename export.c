/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:26:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/30 17:02:55 by brmaria-         ###   ########.fr       */
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

t_env	*get_value(t_env *env, char *name)
{
	    t_env *current = env;

    while (current)
    {
        if (strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
    }
	return (NULL);
}

void set_value(char *str, t_env **env)
{
    char *equal;
    char *name;
    t_env *target;
    int is_append;

	equal = ft_strchr(str, '=');
	is_append = 0;
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
        if (equal)
        {
            char *value = ft_strdup(equal + 1);
            t_env *new = malloc(sizeof(t_env));
            new->name = ft_strdup(name);
            new->value = value;
            new->next = NULL;
            ft_envadd_back(env, new);
        }
        else
        {
            t_env *new = malloc(sizeof(t_env));
            new->name = ft_strdup(name);
            new->value = ft_strdup("");
            new->next = NULL;
            ft_envadd_back(env, new);
        }
        free(name);
        return;
    }
    if (equal)
    {
        if (is_append)
        {
            char *new_value = ft_strjoin(target->value, equal + 1);
            free(target->value);
            target->value = new_value;
        }
        else
        {
            free(target->value);
            target->value = ft_strdup(equal + 1);
        }
    }
    free(name);
}

/// @brief replicating export's behaviours
/// @param args the arguments received from terminal
/// @param env env's list
void	ft_export(char **args, t_shell *shell)
{
	int	i;
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
