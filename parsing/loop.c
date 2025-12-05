/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:27:26 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/05 19:06:24 by brmaria-         ###   ########.fr       */
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
		ft_parser(shell);
		if (ft_is_parent_builtin(shell->cmds))
		{
			execute_builtin(shell);
		}
		else
		{
			ft_openredirs(shell->cmds);
			ft_startproc(shell);
		}
		free(input);	
		ft_clean_tokens(&shell->tokens, NULL);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}
