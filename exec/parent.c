/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:34:43 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/09 17:58:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_pipe(t_token *head);
static int	is_builtin(t_cmd *cmd);

/// @brief calls the builtins in the parent process if there are no pipes
void	parent(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	i = is_pipe(shell->tokens);
	if (i < 0)
		return ;
	else if (i > 0)
		ft_startproc(shell);
	else
	{
		if (is_builtin(shell->cmds))
			execute_builtin(shell);
		else
			ft_startproc(shell);
	}
}

/// @brief checks if there is a pipe in the command line
/// @return -1 on failure, 0 if there is no pipe, 1 if there is a pipe
static int	is_pipe(t_token *head)
{
	t_token	*node;

	if (!head)
		return (-1);
	node = head;
	while (node)
	{
		if (node->type == TOKEN_PIPE)
			return (1);
		node = node->next;
	}
	return (0);
}

static int	is_builtin(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("echo", cmd->cmd, 5))
		return (1);
	if (!ft_strncmp("cd", cmd->cmd, 3))
		return (1);
	if (!ft_strncmp("pwd", cmd->cmd, 4))
		return (1);
	if (!ft_strncmp("export", cmd->cmd, 7))
		return (1);
	if (!ft_strncmp("unset", cmd->cmd, 6))
		return (1);
	if (!ft_strncmp("env", cmd->cmd, 4))
		return (1);
	if (!ft_strncmp("exit", cmd->cmd, 5))
		return (1);
	return (0);
}
