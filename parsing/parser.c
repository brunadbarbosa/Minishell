/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:26:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/14 19:28:17 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*build_cmd_list(t_token *tokens, t_shell *shell);
static void	add_cmd(t_cmd **head, t_cmd *new);


/// @brief generates the command list from the token list
void	ft_parser(t_shell *shell)
{
	if (!shell)
		return ;
	shell->cmds = build_cmd_list(shell->tokens, shell);
}

static t_cmd	*build_cmd_list(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*new;
	t_token	*tok;

	if (!tokens)
		return (NULL);
	head = NULL;
	tok = tokens;
	while (tok && tok->type != TOKEN_EOF)
	{
		if (tok->type == TOKEN_PIPE)
		{
			tok = tok->next;
			continue ;
		}
		new = build_cmd(tok);
		if (!new)
			ft_clean_shell(shell, "Failed to generate t_cmd\n");
		add_cmd(&head, new);
		while (tok && tok->type != TOKEN_PIPE && tok->type != TOKEN_EOF)
			tok = tok->next;
	}
	return (head);
}

static void	add_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*last;

	if (!new || !head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}
