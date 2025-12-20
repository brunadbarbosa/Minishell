/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:20:16 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/17 20:38:39 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief copies from the input to a new_token node
/// @param input the string from the user
/// @param size the size of the token returned by ft_tokensize()
/// @return the new token
t_token	*ft_new_token(char *input, ssize_t size)
{
	t_token	*token;

	if (!input || size == -1)
		return (NULL);
	token = ft_init_token(size);
	if (!token)
		return (NULL);
	ft_strlcpy(token->value, input, (size_t)size + 1);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	if ((token->value[0] == '"' || token->value[0] == '\'')
		&& token->value[size - 1] == token->value[0])
		token->is_quoted = 1;
	else
		token->is_quoted = 0;
	ft_settokentype(token);
	return (token);
}

/// @brief determine the token type
/// @param token the newly created token node
void	ft_settokentype(t_token *token)
{
	char	*value;

	if (!token)
		return ;
	value = token->value;
	if (!ft_strncmp(value, "<<", 2))
		token->type = TOKEN_HEREDOC;
	else if (!ft_strncmp(value, ">>", 2))
		token->type = TOKEN_APPEND;
	else if (!ft_strncmp(value, "<", 1))
		token->type = TOKEN_RED_IN;
	else if (!ft_strncmp(value, ">", 1))
		token->type = TOKEN_RED_OUT;
	else if (!ft_strncmp(value, "|", 1))
		token->type = TOKEN_PIPE;
	else
		token->type = TOKEN_WORD;
}

/// @brief initializes token nodes
/// @param size the size of the string to be allocated as token->value
/// @return the initialized token
t_token	*ft_init_token(ssize_t size)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = malloc(sizeof(char) * (size + 1));
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = -1;
	token->next = NULL;
	return (token);
}

/// @brief finds the size of the next token
/// @param input the current position in the input
/// @return the size of the token, or -1 if the quotes are open
ssize_t	ft_tokensize(char *input)
{
	int		i;
	char	quotes;

	if (!input)
		return (0);
	i = 0;
	quotes = 0;
	if (is_operator(&input[i]))
		return (ft_operatorsize(&input[i]));
	while (input[i])
	{
		if (is_quote(input[i]) && !quotes)
			quotes = input[i++];
		while (quotes && input[i])
		{
			if (input[i] == quotes)
				quotes = 0;
			i++;
		}
		if (!quotes && is_delimiter(&input[i]) && input[i])
			break ;
		if (input[i])
			i++;
	}
	return (ft_openquotes(i, quotes));
}

ssize_t	ft_operatorsize(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	if (input[i] == '|')
		return (1);
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (2);
		else
			return (1);
	}
	else
		return (0);
}
