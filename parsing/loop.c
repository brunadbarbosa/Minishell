/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/10 20:27:42 by adpinhei         ###   ########.fr       */
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
		ft_printf("TOKEN #%i\n [value: %s]\n [type: %i]\n***\n",i, current->value, current->type);
		i++;
		current = current->next;
	}
}
void	loop(t_shell *shell)
{
	char	*input;

	if(!shell)
		return ;
	while (true)
	{
		input = readline("minishell> ");
		ft_exit(&shell, input);
		add_history(input);
		ft_lexer(&shell, input);//puts tolkens
		ft_parser(&shell);//make the cmd list
		free(input);
		ft_clean_shell(&shell, NULL);
	}
	// char		*input;
	// ssize_t		size;
	// t_token		*token;
	// t_token		*token_lst;
	// int		i;

	// token_lst = NULL;
	// token = NULL;
	// while (true)
	// {
	// 	i = 0;
	// 	input = readline("minishell> ");
	// 	if (!ft_strncmp(input, "exit", 5) || !input)
	// 		break ;
	// 	while (input[i])
	// 	{
	// 		while (ft_isspace(input[i]))
	// 			i++;
	// 		size = ft_tokensize(&input[i]);
	// 		if (size == -1)
	// 		{
	// 			ft_putstr_fd("Unclosed quotes\n", 2);
	// 			break;
	// 		}
	// 		token = ft_new_token(&input[i], size);
	// 		ft_add_token(&token_lst, token);
	// 		i += size;
	// 	}
	// 	token = ft_new_token("eof", 3);
	// 	ft_add_token(&token_lst, token);
	// 	free(input);
	// 	ft_printlst(&token_lst);
	// 	if (token_lst)
	// 		ft_clean_token_lst(&token_lst);
	// }
	// free(input);
	// if (token_lst)
	// 	ft_clean_token_lst(&token_lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_init_shell(&shell, envp);
	loop(&shell);
	ft_clean_shell(&shell, NULL);
	return (shell.exit_status);
}
