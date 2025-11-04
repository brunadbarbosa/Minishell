/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/04 17:51:20 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printlst(t_token **lst)
{
	int	i = 1;
	if (!lst || !*lst)
		return ;
	t_token *current = *lst;
	while (current)
	{
		ft_printf("TOKEN #%i\n value: %s\n type: %i\n***\n",i, current->value, current->type);
		i++;
		current = current->next;
	}
}

/// @brief initializes token nodes
/// @param token_size the size of the string to be allocated as token->value
/// @return the initialized token
t_token	*ft_init_token(ssize_t token_size)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = -1;
	token->value = malloc(sizeof(char *) * token_size);//calloc?
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

/// @brief finds the size of the next token
/// @param input the current position in the input
/// @return the size of the token, or -1 if the quotes are open
/*consider removing spaces before calling this function*/
ssize_t	ft_tokensize(char *input)
{
	int		i;
	char	quotes;

	if (!input)
		return (0);
	i = 0;
	quotes = 0;
	while (input[i])
	{
		if (is_quote(input[i]) && !quotes)
		{
			quotes = input[i];
			i++;
		}
		while (quotes && input[i])
		{
			if (input[i] == quotes)
				quotes = 0;
			i++;
		}
		if (!quotes && is_delimiter(&input[i]) && input[i])
		{
			if (!ft_strncmp(&input[i], "<<", 2) || !ft_strncmp(&input[i], ">>", 2))
				i += 2;
			else
				i++;
			break ;
		}
		if (input[i])
			i++;
	}
	if (quotes)
		return (-1);
	return (i);
}

/// @brief adds newly generated token nodes to the token list
/// @param lst the head of the token list
/// @param new the new token to be added to the list
void	ft_add_token(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

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
	token->value = ft_memmove(token->value, input, (size_t)size);
	token->value[(int)size] = '\0';
	return (token);
}

int	main(void)
{
	char	*input;
	ssize_t	size;
	t_token	*token;
	t_token	*token_lst;
	int		i;

	token_lst = NULL;
	token = NULL;
	while (true)
	{
		i = 0;
		input = readline("minishell>");
		if (!ft_strncmp(input, "exit", 5) || !input)
			break ;
		while (input[i])
		{
			while (ft_isspace(input[i]))
				i++;
			size = ft_tokensize(&input[i]);
			if (size == -1)
			{
				ft_putstr_fd("Failed to read token size\n", 2);
				break;
			}
			token = ft_new_token(&input[i], size);
			ft_add_token(&token_lst, token);
			i += size;
		}
		free(input);
		ft_printlst(&token_lst);
		if (token_lst)
			ft_clean_token_lst(&token_lst);
	}
	free(input);
	if (token_lst)
		ft_clean_token_lst(&token_lst);
}
