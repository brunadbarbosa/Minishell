/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:19:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/05 19:06:38 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env *env);
void	ft_echo(char **args, t_shell *shell);
void	ft_export(char **args, t_shell *shell);
void	ft_pwd(t_env *env);
void	ft_unset(char **args, t_env *env, t_shell *shell);
void	ft_cd(t_shell *shell);
void	ft_exit(char **args, char *cmd, t_shell *shell);

void	execute_builtin(t_shell *shell)
{
	char **args;
	
	t_env	*env;
	char	*cmd;

	// if(!shell->cmds)
	// {
	// 	return ;
	// }
	args = shell->cmds->args + 1;
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
		ft_exit(args, cmd, shell);
	else
	{
		shell->exit_status = 127;
		ft_putstr_fd(" command not found\n", 2);
	}
}


int	ft_is_parent_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
		return (1);
	if (ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)) == 0 
		|| ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)) == 0
			|| ft_strncmp(cmd->cmd, "export", ft_strlen(cmd->cmd)) == 0
				|| ft_strncmp(cmd->cmd, "unset", ft_strlen(cmd->cmd)) == 0
					|| ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)) == 0
						|| ft_strncmp(cmd->cmd, "pwd", ft_strlen(cmd->cmd)) == 0
							|| ft_strncmp(cmd->cmd, "env", ft_strlen(cmd->cmd)) == 0)
		return (1);
	return (0);
}
