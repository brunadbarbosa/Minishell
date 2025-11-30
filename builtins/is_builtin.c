/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:19:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/30 17:03:05 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env *env);
void	ft_echo(char **args, t_shell *shell);
void	ft_export(char **args, t_shell *shell);
void	ft_pwd(t_env *env);
void	ft_unset(char **args, t_env *env, t_shell *shell);
void	ft_cd(t_shell *shell);
void	my_exit(char **args, char *cmd, t_shell *shell);

void	check_is_builtin(t_shell *shell)
{
	char **args = shell->cmds->args + 1;
	
	t_env	*env;
	char	*cmd;
	
	env = shell->env;
	cmd = shell->cmds->cmd;
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1) == 0)
		ft_pwd(env);
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1) == 0)
		ft_echo(args, shell);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd) + 1) == 0)
		ft_env(env);		
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd) + 1) == 0)
		ft_export(args, shell);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1) == 0)
		ft_unset(args, env, shell);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1) == 0)
	 	ft_cd(shell);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1) == 0)
		my_exit(args, cmd, shell);
	else
	{
		shell->exit_status = 127;
		ft_putstr_fd(" command not found\n", 2);
	}
}
