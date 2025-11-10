/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_maker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:06:06 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/10 18:11:26 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief adds t_cmd to the cmd list
/// @param token the head to the token list
/// @param cmd_lst the head to the cmd list
void	ft_add_cmd(t_token *token, t_cmd *cmd_lst)
{
	t_token	*node;

	if (!token)
		return ;
	node = token;
	while (node->type != TOKEN_EOF)
	{
		if (!cmd_lst)
			cmd_lst = ft_makecmd(node);
		else
		{
			while (cmd_lst->next)
				cmd_lst = cmd_lst->next;
			cmd_lst->next = ft_makecmd(node);
		}
		node = node->next;
	}
}

/// @brief creates the t_cmd node
/// @param token the head to the token list
/// @return the t_cmd node to be added to the execution list
t_cmd	*ft_makecmd(t_token *token)
{
	t_cmd	*cmd;
	t_token	*node;
	int		found_cmd;
	int		i;

	if (!token)
		return (NULL);
	ft_cmd_init(cmd);
	found_cmd = 0;
	node = token;
	i = 0;
	while (node->type != TOKEN_EOF && node->type != TOKEN_PIPE)
	{
		if (node->type == TOKEN_WORD)
		{
			if (found_cmd == 0)
			{
				cmd->cmd = ft_strdup(token->value);
				found_cmd = 1;
			}
			else
			{
				cmd->args[i] = ft_strdup(token->value);
				i++;
			}
		}
		if (token->type > 1 && token->type < 6)
		{
			if (token->type == TOKEN_APPEND)
				cmd->redirs->type = REDIR_APPEND;
			else if (token->type == TOKEN_HEREDOC)
				cmd->redirs->type = REDIR_HERE;
			else if (token->type == TOKEN_RED_IN)
				cmd->redirs->type = REDIR_IN;
			else if (token->type == TOKEN_RED_OUT)
				cmd->redirs->type = REDIR_OUT;
			if (node->next)
				node = node->next;
			if (node->type == TOKEN_WORD)
				cmd->redirs->file = ft_strdup(token->value);
			if (node->next->type == TOKEN_PIPE)
			{
				cmd->next = node->next;
				break ;
			}
		}
		node = node->next;
	}
	return (cmd);
}

void	ft_cmd_init(t_cmd *cmd)
{
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		ft_putstr_fd("Failed to allocate for t_cmd\n", 2);
		return ;
	}
	cmd->redirs = ft_calloc(1, sizeof(t_redir));;
	if (!cmd->redirs)
	{
		free(cmd);
		ft_putstr_fd("Failed to allocate t_redir\n", 2);
		return ;
	}
	cmd->redirs->fd = -1;
}
