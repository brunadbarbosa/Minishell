/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/06 10:21:23 by adpinhei         ###   ########.fr       */
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
int	main(void)
{
	char		*input;
	ssize_t		size;
	t_token		*token;
	t_token		*token_lst;
	int		i;

	token_lst = NULL;
	token = NULL;
	while (true)
	{
		i = 0;
		input = readline("minishell> ");
		if (!ft_strncmp(input, "exit", 5) || !input)
			break ;
		while (input[i])
		{
			while (ft_isspace(input[i]))
				i++;
			size = ft_tokensize(&input[i]);
			if (size == -1)
			{
				ft_putstr_fd("Unclosed quotes\n", 2);
				break;
			}
			token = ft_new_token(&input[i], size);
			ft_add_token(&token_lst, token);
			i += size;
		}
		token = ft_new_token("eof", 3);
		ft_add_token(&token_lst, token);
		free(input);
		ft_printlst(&token_lst);
		if (token_lst)
			ft_clean_token_lst(&token_lst);
	}
	free(input);
	if (token_lst)
		ft_clean_token_lst(&token_lst);
}
