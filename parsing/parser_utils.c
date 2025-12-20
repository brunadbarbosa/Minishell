/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:42:08 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 18:35:16 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir_type	redirtype(t_token_type type)
{
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (type == TOKEN_HEREDOC)
		return (REDIR_HERE);
	if (type == TOKEN_RED_IN)
		return (REDIR_IN);
	if (type == TOKEN_RED_OUT)
		return (REDIR_OUT);
	else
		return (-1);
}

void	ft_initredir(t_redir *redir, t_token *tk)
{
	if (!redir || !tk)
		return ;
	redir->file = ft_strdup(tk->next->value);
	redir->fd = -1;
	redir->type = redirtype(tk->type);
	redir->next = NULL;
}

int	ft_buildnextcmd(t_cmd **current, t_cmd *head)
{
	(*current)->next = ft_calloc(1, sizeof(t_cmd));
	if (!(*current)->next)
	{
		ft_clean_cmd_lst(&head, "Unable to allocate t_cmd\n");
		return (1);
	}
	(*current) = (*current)->next;
	return (0);
}

int	ft_initcmdlist(t_token **tk, t_token *tks, t_cmd **h, t_cmd **c)
{
	*h = ft_calloc(1, sizeof(t_cmd));
	if (!*h)
		return (1);
	*c = *h;
	*tk = tks;
	return (0);
}
