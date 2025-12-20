/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:26:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 18:35:13 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*build_cmd_list(t_token *tokens);
static void		buildredir(t_cmd *cmd, t_token *tk);
static void		buildcmd(t_cmd *cmd, t_token *tk);
static char		**buildargs(char **args, char *str);

/// @brief generates the command list from the token list
void	ft_parser(t_shell *shell)
{
	if (!shell || !shell->tokens)
		return ;
	shell->cmds = build_cmd_list(shell->tokens);
}

static t_cmd	*build_cmd_list(t_token *tokens)
{
	t_token	*tk;
	t_cmd	*head;
	t_cmd	*current;

	if (ft_initcmdlist(&tk, tokens, &head, &current))
		return (NULL);
	while (tk)
	{
		if (tk->type > 1 && tk->type < 6)
		{
			buildredir(current, tk);
			tk = tk->next;
		}
		else if (tk->type == TOKEN_WORD)
			buildcmd(current, tk);
		else if (tk->type == TOKEN_PIPE)
		{
			if (ft_buildnextcmd(&current, head))
				return (NULL);
		}
		if (!tk->next)
			break ;
		tk = tk->next;
	}
	return (head);
}

static void	buildredir(t_cmd *cmd, t_token *tk)
{
	t_redir	*redir;
	t_redir	*tmp;

	if (!cmd || !tk || !tk->next)
		return ;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	ft_initredir(redir, tk);
	if (!redir->file)
	{
		free(redir);
		return ;
	}
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

static void	buildcmd(t_cmd *cmd, t_token *tk)
{
	if (!cmd || !tk)
		return ;
	if (!cmd->cmd)
	{
		cmd->cmd = ft_strdup(tk->value);
		cmd->args = malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return ;
		cmd->args[0] = ft_strdup(tk->value);
		cmd->args[1] = NULL;
	}
	else
		cmd->args = buildargs(cmd->args, tk->value);
}

static char	**buildargs(char **args, char *str)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (args);
	i = 0;
	while (args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = ft_strdup(str);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}
