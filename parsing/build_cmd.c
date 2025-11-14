/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:04:53 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/14 19:42:29 by adpinhei         ###   ########.fr       */
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
	cmd->cmd = find_cmd(token);
	cmd->args = find_args(token);
	cmd->redirs = find_redirs(token);
	cmd->next = NULL;
	return (cmd);
}

static char	*find_cmd(t_token *token)
{
	t_token	*current;
	char	*cmd;

	if (!token)
		return (NULL);
	current = token;
	while (current && current->type != TOKEN_EOF && current->type != TOKEN_PIPE)
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
	args = NULL;
	alloc_args(&args, token);
	if (!args)
		return (NULL);
	while (current && current->type != TOKEN_WORD && current->type != TOKEN_EOF)
		current = current->next;
	if (!current || current->type != TOKEN_WORD)
		return (args);
	current = current->next;
	while (current && current->type == TOKEN_WORD)
	{
		args[i] = ft_strdup(current->value);
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
	while (current && current->type != TOKEN_EOF && current->type != TOKEN_WORD)
		current = current->next;
	if (!current || current->type != TOKEN_WORD)
	{
		*args = malloc(sizeof(char *));
		if (!*args)
			(*args)[0] = NULL;
		return ;
	}
	if (current->type == TOKEN_WORD)
		current = current->next;
	while (current && current->type == TOKEN_WORD)
	{
		i++;
		current = current->next;
	}
	*args = malloc(sizeof(char *));
	if (!*args)
		ft_putstr_fd("Failed at alloc_args\n", 2);
}
