/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:27:26 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/16 18:33:14 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printcmd(t_shell *shell);

int	ft_have_something(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 32 || line[i] == '\t'))
		i++;
	if (line[i])
		return (1);
	return (0);
}

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
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		add_history(input);
		if (!input[0] || !ft_have_something(input) || !strcmp(input, "$EMPTY"))
        {
            free(input);
            continue;
        }
		ft_lexer(shell, input);
		ft_syntax(shell);
		ft_parser(shell);
		ft_openredirs(shell->cmds, shell);
		parent(shell);
		free(input);
		ft_clean_tokens(&shell->tokens, NULL);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}
