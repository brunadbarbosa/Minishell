/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/08 18:11:37 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/minishell.h"

/// @brief the shell loop. Goes on purposeful exit from user
/// @param shell the master struct
void	loop(t_shell *shell)
{
	char	*input;

	if (!shell)
		return ;
	while (true)
	{
		input = readline("minishell> ");
		add_history(input);
		ft_lexer(shell, input);
		ft_syntax(shell);
		// ft_printlst(shell);
		ft_parser(shell);
		// check_is_builtin(shell);
//		ft_printcmd(shell);
		free(input);
		ft_clean_tokens(&shell->tokens, NULL);
		ft_openredirs(shell->cmds, shell);
//		print_env(shell);
		ft_startproc(shell);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}
