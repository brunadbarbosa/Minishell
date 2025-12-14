/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:06:57 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/14 20:21:26 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_add_token(t_token **lst, t_token *new);
static void	ft_rmempty(t_token **tokens);
static int	ft_isemptytoken(t_token *token);
static void	ft_removenode(t_token **tokens, t_token **curr, t_token *prev);

/// @brief tokenizes the input
/// @param input line from the user
void	ft_lexer(t_shell *shell, char *input)
{
	t_token	*token_node;
	ssize_t	size;
	int		i;

	if (!input)
		return ;
	i = 0;
	if (!ft_strncmp(input, "$EMPTY", 6))
		input += 6;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		size = ft_tokensize(&input[i]);
		if (size == -1)
			return (ft_putstr_fd("Unclosed quotes\n", 2));
		token_node = ft_new_token(&input[i], size);
		if (!token_node)
			return (ft_clean_shell(shell, "Failed to allocate token\n"));
		ft_add_token(&shell->tokens, token_node);
		i += size;
	}
	ft_expand(&shell->tokens, shell);
	ft_rmempty(&shell->tokens);
}

/// @brief adds newly generated token nodes to the token list
/// @param lst the head of the token list
/// @param new the new token to be added to the list
static void	ft_add_token(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

/// @brief removes tokens with empty value
static void	ft_rmempty(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (ft_isemptytoken(curr))
			ft_removenode(tokens, &curr, prev);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

static int	ft_isemptytoken(t_token *token)
{
	int	i;

	if (token->type != TOKEN_WORD)
	{
		i = 0;
		while (token->value[i] && ft_isspace(token->value[i]))
			i++;
		return (token->value[i] == '\0');
	}
	return (0);
}

static void	ft_removenode(t_token **tokens, t_token **curr, t_token *prev)
{
	t_token	*next;

	next = (*curr)->next;
	if (prev == NULL)
		*tokens = next;
	else
		prev->next = next;
	free((*curr)->value);
	free(*curr);
	*curr = next;
}
