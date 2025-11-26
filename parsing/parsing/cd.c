/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:09:43 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/25 17:17:11 by brmaria-         ###   ########.fr       */
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
	if (args[0] == NULL )
	{
		
		printf("cheguei aqui 2\n");
		tmp = shell->env;
		while (tmp)
		{
			if (ft_strncmp(tmp->name, "HOME", 4) == 0)
				return(ft_strdup(tmp->value));
			tmp = tmp->next;
		}
		return (NULL);
	}
	return (ft_strdup(args[0]));
}

char	*get_current_path(void)
{
	char	*cwd;
	int	len;

	len = 1024;
	cwd = malloc(len);
	if (!cwd)
		return (NULL);
    while (getcwd(cwd, len) == NULL)
    {
        if (errno != ERANGE)
        {
            free(cwd);
            return NULL;
        }
        cwd = get_bigger_buffer(cwd, len, len * 2);
        if (!cwd)
            return NULL;
        len *= 2;
    }
	return (cwd);
}

void	ft_cd(t_shell *shell)
{
	char	**args;
	char	*pwd;
	char	*old_pwd;
	int		change_dir;

	args = shell->cmds->args + 1;
	if (!args[0] || !args[0][0])
	{
		printf("cheguei aqui\n");
		old_pwd = get_current_path();
		change_dir = chdir(copy_from_env(args, shell));
		pwd = get_current_path();
		change_env(old_pwd, pwd, shell);
		return ;
	}
	if (args[0] && args[1])
	{
		printf("minishell: cd: too many arguments.\n");
		return ;
	}
	old_pwd = get_current_path();
	change_dir = chdir(args[0]);
	if (change_dir == -1)
	{
		perror("cd");
		return ;
	}
	pwd = get_current_path();
	change_env(old_pwd, pwd, shell);
}
