/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:34:43 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/09 17:58:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_pipe(t_token *head);

/// @brief calls the builtins in the parent process if there are no pipes
void	parent_builtin(t_shell *shell)
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
		check_is_builtin(shell);
	//check for pipes
	//check for parent builtins
	//call builtin function
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
