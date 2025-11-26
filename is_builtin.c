/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:19:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/24 14:41:00 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

void	check_is_builtin(t_shell *shell)
{
	t_env	*env;
	char	*cmd;
	
	env = shell->env;
	cmd = shell->cmds->cmd;
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		ft_pwd(env);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		ft_echo(shell->cmds->args);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		ft_env(env);		
	else if (ft_strncmp(cmd, "export", 6) == 0)
		ft_export(shell->cmds->args, env);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
	{
		ft_unset(shell->cmds->args, &env);
		ft_env(env);
	}
	else if (ft_strncmp(cmd, "cd", 5) == 0)
		ft_cd(env, shell->cmds->args);
}
