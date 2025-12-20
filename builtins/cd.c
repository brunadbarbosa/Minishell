/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:09:43 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/20 18:25:33 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_current_path(void)
{
	char	*cwd;
	int		len;

	len = 1024;
	cwd = malloc(len);
	if (!cwd)
		return (NULL);
	while (getcwd(cwd, len) == NULL)
	{
		if (errno != ERANGE)
		{
			free(cwd);
			return (NULL);
		}
		cwd = get_bigger_buffer(cwd, len, len * 2);
		if (!cwd)
			return (NULL);
		len *= 2;
	}
	return (cwd);
}

static int	cd_to_oldpwd(t_shell *shell, char *old_pwd)
{
	t_env	*path;

	path = get_value(shell->env, "OLDPWD");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		free(old_pwd);
		shell->exit_status = 1;
		return (1);
	}
	if (chdir(path->value) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		shell->exit_status = 1;
		return (1);
	}
	ft_putendl_fd(path->value, STDOUT_FILENO);
	return (0);
}

int	change_directory(char **args, t_shell *shell, char *old_pwd)
{
	if (!args[0] || !args[0][0])
		return (cd_to_home(args, shell, old_pwd));
	if (args[1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		free(old_pwd);
		shell->exit_status = 1;
		return (1);
	}
	if (ft_strcmp(args[0], "-") == 0)
		return (cd_to_oldpwd(shell, old_pwd));
	if (chdir(args[0]) == -1)
	{
		ft_putstr_fd("Error while changing directories\n", 2);
		free(old_pwd);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	*pwd;

	pwd = get_current_path();
	if (!pwd)
		return ;
	change_env(old_pwd, pwd, shell);
	free(pwd);
}

void	ft_cd(char **args, t_shell *shell)
{
	char	*old_pwd;

	old_pwd = get_current_path();
	if (!old_pwd)
		return ;
	if (change_directory(args, shell, old_pwd))
		return ;
	update_pwd_env(shell, old_pwd);
	free(old_pwd);
	shell->exit_status = 0;
}
