/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/02 19:01:07 by adpinhei         ###   ########.fr       */
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
		ft_exit(shell, input); //that goes out. Replace this for a simple quote syntax checker
		add_history(input);
		ft_lexer(shell, input);
		ft_syntax(shell);
//		ft_printlst(shell);
		ft_parser(shell);
//		ft_printcmd(shell);
		free(input);
		ft_clean_tokens(&shell->tokens, NULL);
		ft_openredirs(shell->cmds);
		ft_startproc(shell);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}
