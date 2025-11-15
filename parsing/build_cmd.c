/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:04:53 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/15 20:18:23 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_cmd(t_token *token);
static char	**find_args(t_token *token);
static void	alloc_args(char ***args, t_token *token);


t_cmd	*build_cmd(t_token *token)
{
	t_cmd	*cmd;

	if (token->type == TOKEN_EOF || !token)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redirs = find_redirs(token);
	cmd->cmd = find_cmd(token);
	cmd->args = find_args(token);
	if (!cmd->cmd || !cmd->redirs/* || !cmd->args*/)
	{
		ft_free_args(cmd->args);
		if (cmd->cmd)
			free(cmd->cmd);
		ft_clean_redirs(&cmd->redirs);
		free(cmd);
		return (NULL);
	}
	cmd->next = NULL;
	return (cmd);
}

static char	*find_cmd(t_token *token)
{
	t_token	*current;
	char	*cmd;
	int		redir;

	if (!token)
		return (NULL);
	current = token;
	redir = 0;
	while (current && current->type != TOKEN_EOF && current->type != TOKEN_PIPE)
	{
		if (current->type > 1 && current->type < 6)
			redir = 1;
		if (current->type == TOKEN_WORD && redir)
		{
			current = current->next;
			redir = 0;
		}
		if (current->type == TOKEN_WORD && !redir)
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
	args = NULL;
	alloc_args(&args, token);
	if (!args)
		return (NULL);
	while (current && current->type != TOKEN_WORD && current->type != TOKEN_EOF)
		current = current->next->next;
	if (!current || current->type != TOKEN_WORD)
	{
		free(args);
		return (NULL);
	}
	current = current->next;
	while (current && current->type == TOKEN_WORD)
	{
		args[i] = ft_strdup(current->value);
		if (!args[i])
		{
			ft_free_args(args);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

static void	alloc_args(char ***args, t_token *token)
{
	int		i;
	t_token	*current;

	current = token;
	i = 0;
	while (current && current->type != TOKEN_WORD)
		current = current->next;
	if (!current || current->type != TOKEN_WORD)
	{
		*args = NULL;
		return ;
	}
	if (current->type == TOKEN_WORD)
		current = current->next;
	while (current && current->type == TOKEN_WORD)
	{
		i++;
		current = current->next;
	}
	*args = ft_calloc(i + 1, sizeof(char *));
}
