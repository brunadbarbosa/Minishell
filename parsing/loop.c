/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2025/12/02 19:43:02 by adpinhei         ###   ########.fr       */
=======
/*   Updated: 2025/12/01 17:48:24 by adpinhei         ###   ########.fr       */
>>>>>>> main
=======
/*   Updated: 2025/12/01 16:41:45 by brmaria-         ###   ########.fr       */
>>>>>>> 34c332dfdc4124a4b0ad3bfa44fb57c5539ee2ad
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
<<<<<<< HEAD
		ft_exit(shell, input); //that goes out. Replace this for a simple quote syntax checker
		add_history(input);
		ft_lexer(shell, input);
		ft_syntax(shell);
//		ft_printlst(shell);
=======
		my_exit(shell, input);
		add_history(input);
		ft_lexer(shell, input);
		ft_syntax(shell);
		// ft_printlst(shell);
>>>>>>> 34c332dfdc4124a4b0ad3bfa44fb57c5539ee2ad
		ft_parser(shell);
//		ft_printcmd(shell);
		free(input);
		ft_clean_tokens(&shell->tokens, NULL);
		ft_openredirs(shell->cmds);
//		print_env(shell);
		ft_startproc(shell);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}
