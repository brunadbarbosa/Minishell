/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:37:50 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/20 18:36:55 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_env(char *old_pwd, char *new_pwd, t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->name, "OLDPWD", 6) == 0)
		{
			free(env->value);
			env->value = ft_strdup(old_pwd);
		}
		else if (ft_strncmp(env->name, "PWD", 3) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_pwd);
		}
		env = env->next;
	}
}

char	*get_bigger_buffer(char *prev, int prev_len, int new_prev_len)
{
	char	*new_cwd;

	new_cwd = malloc(new_prev_len);
	if (!new_cwd)
	{
		free(prev);
		return (NULL);
	}
	ft_memcpy(new_cwd, prev, prev_len);
	free(prev);
	return (new_cwd);
}

char	*copy_from_env(char **args, t_shell *shell)
{
	t_env	*tmp;

	if (args[0] == NULL)
	{
		tmp = shell->env;
		while (tmp)
		{
			if (ft_strncmp(tmp->name, "HOME", 4) == 0)
				return (ft_strdup(tmp->value));
			tmp = tmp->next;
		}
		return (NULL);
	}
	return (ft_strdup(args[0]));
}

int	cd_to_home(char **args, t_shell *shell, char *old_pwd)
{
	char	*path;

	path = copy_from_env(args, shell);
	if (!path || chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		free(path);
		free(old_pwd);
		shell->exit_status = 1;
		return (1);
	}
	free(path);
	return (0);
}
