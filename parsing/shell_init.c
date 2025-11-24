/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:07:18 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/20 16:51:05 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*ft_env(char **envp);
static t_env	*new_env_node(char *entry);
static void		env_add_back(t_env **env, t_env *new);
static void		ft_shlvl(t_env *env);

/// @brief initialize the super struct t_shell
/// @param shell the super struct
/// @param envp the pointer to the environment variables
void	ft_init_shell(t_shell *shell, char **envp)
{
	if (!shell)
		return ;
	if (!envp)
	{
		ft_putstr_fd("No environment\n", 2);
		return ;
	}
	shell->std_in = STDIN_FILENO;
	shell->std_out = STDOUT_FILENO;
	shell->cmds = NULL;
	shell->tokens = NULL;
	shell->exit_status = 0;
	shell->env = ft_env(envp);
	ft_shlvl(shell->env);
}

static t_env	*ft_env(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	env = NULL;
	i = 0;
	while (envp[i])
	{
		node = new_env_node(envp[i]);
		if (!node)
			return (NULL);
		env_add_back(&env, node);
		i++;
	}
	return (env);
}

static t_env	*new_env_node(char *entry)
{
	t_env	*node;
	int		j;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	j = 0;
	while (entry[j] && entry[j] != '=')
		j++;
	node->name = malloc(sizeof(char) * (j + 1));
	if (!node->name)
		return (NULL);
	ft_strlcpy(node->name, entry, j + 1);
	if (entry[j] == '=')
		node->value = ft_strdup(entry + j + 1);
	else
		node->value = ft_strdup("");
	if (!node->value)
		return (NULL);
	node->next = NULL;
	return (node);
}

static void	env_add_back(t_env **env, t_env *new)
{
	t_env	*temp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

static void	ft_shlvl(t_env *env)
{
	t_env	*current;
	int		tmp;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		if (!ft_strncmp(current->name, "SHLVL", 5))
		{
			tmp = ft_atoi(current->value);
			free(current->value);
			current->value = ft_itoa(tmp + 1);
			return ;
		}
		current = current->next;
	}
}
