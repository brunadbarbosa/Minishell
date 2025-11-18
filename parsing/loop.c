/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/18 20:50:20 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_init_shell(&shell, envp);
//	print_env(&shell);
	loop(&shell);
	ft_clean_shell(&shell, NULL);
	return (shell.exit_status);
}

void	loop(t_shell *shell)
{
	char	*input;

	if (!shell)
		return ;
	while (true)
	{
		input = readline("minishell> ");
		ft_exit(shell, input);
		add_history(input);
		ft_lexer(shell, input);//puts tolkens
		ft_syntax(shell); //verify valid syntax
//		ft_printlst(shell);//remove this tester
		ft_parser(shell);//make the cmd list
		ft_printcmd(shell);//remove this tester
		free(input);
		ft_clean_tokens(&shell->tokens, NULL);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}
