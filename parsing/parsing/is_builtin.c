/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:19:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/26 17:36:53 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env *env);
void	ft_echo(char **args);
void	ft_export(char **args, t_shell *shell);
void	ft_pwd(t_env *env);
void	ft_unset(char **args, t_env **env);
void	ft_cd(t_shell *shell);
void	my_exit(char **args, char *cmd, t_shell *shell);

void	check_is_builtin(t_shell *shell)
{

	char **args = shell->cmds->args + 1;
	
	t_env	*env;
	char	*cmd;
	
	env = shell->env;
	cmd = shell->cmds->cmd;
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		ft_pwd(env);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		ft_echo(args);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		ft_env(env);		
	else if (ft_strncmp(cmd, "export", 6) == 0)
		ft_export(args, shell);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
	{
		ft_unset(args, &env);
		ft_env(env);
	}
	 else if (ft_strncmp(cmd, "cd", 2) == 0)
	 	ft_cd(shell);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		my_exit(args, cmd, shell);
}
