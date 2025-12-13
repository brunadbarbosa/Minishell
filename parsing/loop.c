/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:27:26 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/13 15:59:07 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

//int	wrong_fds(t_shell *shell);
int  ft_redcmd(int type, int fd);
int	get_redir(t_redir *red, t_shell *shell);

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
		if (!input[0] || !ft_have_something(input) || !strcmp(input, "$EMPTY"))
			continue ;
		if (!ft_strncmp(input, "$EMPTY", 6))
			input += 6;
		add_history(input);
		ft_lexer(shell, input);
		ft_syntax(shell);
		ft_parser(shell);
		//nft_printcmd(shell);
		ft_openredirs(shell->cmds, shell);
		parent(shell);
		if (!ft_strncmp(input - 6, "$EMPTY", 6))
			input -= 6;
		free(input);
		ft_clean_tokens(&shell->tokens, NULL);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}



// int	wrong_fds(t_shell *shell)
// {
// 	t_redir *redirs;

// 	redirs = shell->cmds->redirs;
// 	while(redirs)
// 	{
// 		if (get_redir(redirs, shell))
// 		{
// 			ft_redcmd(redirs->type, -1);

// 			return (1);
// 		}
// 		redirs = redirs->next;
// 	}
// 	return (0);
// }
