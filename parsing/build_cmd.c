/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:04:53 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/12 18:29:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*build_cmd(t_token *token)
{
	t_cmd	*cmd;

	if (token->type == TOKEN_EOF || !token)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = find_cmd(token);
	cmd->args = find_args(token);
	cmd->redirs = find_redirs(token);
}

static char	*find_cmd(t_token *token)
{
	t_token	*current;
	char	*cmd;

	if (!token)
		return (NULL);
	current = token;
	while (current->type != TOKEN_EOF && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD)
		{
			cmd = ft_strdup(current->value);
			return (cmd);
		}
		current = current->next;
	}
	return (NULL);
}

static char	**find_args(t_token *token)
{
	t_token	*current;
	char	**args;
	int		i;

	if (!token)
		return (NULL);
	current = token;
	i = 0;
	while (current->type != TOKEN_WORD && current->type != TOKEN_EOF)
		current = current->next;
	if (current->type != TOKEN_WORD)
		return (NULL);
	while (current->type == TOKEN_WORD)
	{
		args[i] = ft_strdup(current->value);
		i++;
		current = current->next;
	}
	args[i] = '\0';
	return (args);
}

t_redir	*find_redirs(t_token *token)
{
	t_redir	*redir;
	t_redir	*node;
	t_token	*current;

	if (!token)
		return (NULL);
	current = token;
	while (current->type != TOKEN_EOF && current->type != TOKEN_PIPE)
	{
		if (current->type > 1 && current->type < 6)
		{
			node = redir_node(current);
			add_redir(&redir, node);
			ft_clean_redirs(node);
		}
		current = current->next;
	}
	return (redir);
}

t_redir	*redir_node(t_token *token)
{
	t_redir	*node;

	if (!token)
		return (NULL);
	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->fd = -1;
	node->type = redir_type(token);
	node->file = ft_strdup(token->next->value);
	node->next = NULL;
}

int	redir_type(t_token *token)
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

void	add_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	last = NULL;
}
