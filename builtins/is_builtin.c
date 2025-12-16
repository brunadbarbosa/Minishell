/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:19:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/15 19:03:58 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	is_directory(char *cmd, t_shell *shell);

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
	else if (ft_strchr(cmd->cmd, 47))
		is_directory(cmd->cmd, shell);
	else
		shell->exit_status = 127;
}

void	print_msg(t_shell *shell, char *cmd, char *str, int status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(str, 2);
	shell->exit_status = status;
}

void	is_directory(char *cmd, t_shell *shell)
{
    struct stat sb;

    if (stat(cmd, &sb) == -1)
		return (print_msg(shell, cmd, " No such file or directory\n", 127));
    else if (S_ISDIR(sb.st_mode))
		return (print_msg(shell, cmd, ": Is a directory\n", 126));
    else if (S_ISREG(sb.st_mode))
    {
        if (access(cmd, X_OK) == 0)
            return ;
        else
            print_msg(shell, cmd, ": Permission denied\n", 126);
        return ;
    }
    print_msg(shell, cmd, ": Not a directory\n", 127);
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
