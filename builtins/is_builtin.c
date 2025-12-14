/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:19:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/14 14:58:16 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	char	**args;
	t_env	*env;

	args = cmd->args + 1;
	env = shell->env;
	if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		ft_pwd(env);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		ft_echo(args, shell);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		ft_export(args, shell, env);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		ft_unset(args, shell);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		ft_cd(args, shell);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ft_exit(args, cmd->cmd, shell);
	else
		shell->exit_status = 127;
}

int	ft_is_parent_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
		return (1);
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0
		|| ft_strncmp(cmd->cmd, "exit", 5) == 0
		|| ft_strncmp(cmd->cmd, "export", 7) == 0
		|| ft_strncmp(cmd->cmd, "unset", 6) == 0
		|| ft_strncmp(cmd->cmd, "echo", 5) == 0
		|| ft_strncmp(cmd->cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd->cmd, "env", 4) == 0)
		return (1);
	return (0);
}
