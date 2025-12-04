/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:27:26 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/04 17:37:37 by brmaria-         ###   ########.fr       */
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
		ft_openredirs(shell->cmds);
//		print_env(shell);
		ft_startproc(shell);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}
