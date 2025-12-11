/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:27:26 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/11 13:04:22 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	wrong_fds(t_shell *shell);
int  ft_redcmd(int type, int fd);
int	get_redir(t_redir *red, t_shell *shell);

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
		if (!shell->cmds->next && wrong_fds(shell))
		{
			shell->exit_status = 1;
		}
		else if (ft_is_parent_builtin(shell->cmds) && !shell->cmds->next)
		{
			execute_builtin(shell->cmds, shell);
			if (shell->exit_status == 127)
				ft_putstr_fd(" command not found", 2);
		}
		else
		{
			ft_openredirs(shell->cmds, shell);
			ft_startproc(shell);
		}
		free(input);	
		ft_clean_tokens(&shell->tokens, NULL);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}

int	wrong_fds(t_shell *shell)
{
	t_redir *redirs;

	redirs = shell->cmds->redirs;
	while(redirs)
	{
		if (get_redir(redirs, shell))
		{
			ft_redcmd(redirs->type, -1);

			return (1);
		}
		redirs = redirs->next;
	}
	return (0);
}
