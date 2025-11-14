/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:42:27 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/14 14:44:52 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_redir	*redir_node(t_token *token);
static int	redir_type(t_token *token);
static void	add_redir(t_redir **lst, t_redir *new);

t_redir	*find_redirs(t_token *token)
{
	t_redir	*redir;
	t_redir	*node;
	t_token	*current;

	if (!token)
		return (NULL);
	redir = NULL;
	current = token;
	while (current->type != TOKEN_EOF && current->type != TOKEN_PIPE)
	{
		if (current->type > 1 && current->type < 6)
		{
			node = redir_node(current);
			if (node)
				add_redir(&redir, node);
		}
		current = current->next;
	}
	return (redir);
}


static t_redir	*redir_node(t_token *token)
{
	t_redir	*node;

	if (!token || !token->next)
		return (NULL);
	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->fd = -1;
	node->type = redir_type(token);
	node->file = ft_strdup(token->next->value);
	node->next = NULL;
	return (node);
}

static int	redir_type(t_token *token)
{
	if (token->type == TOKEN_RED_IN)
		return (REDIR_IN);
	else if (token->type == TOKEN_RED_OUT)
		return (REDIR_OUT);
	else if (token->type == TOKEN_HEREDOC)
		return (REDIR_HERE);
	else if (token->type == TOKEN_APPEND)
		return (REDIR_APPEND);
	else
		return (-1);
}

static void	add_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
