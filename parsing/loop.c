/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/20 15:28:43 by adpinhei         ###   ########.fr       */
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
		ft_lexer(shell, input);
		ft_syntax(shell);
//		ft_printlst(shell);
		ft_parser(shell);
		ft_printcmd(shell);
		free(input);
		ft_clean_tokens(&shell->tokens, NULL);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}
