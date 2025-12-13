/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:20 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/13 16:18:11 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_redir(t_redir *red, t_shell *shell);
static char	*gen_filename(void);

void	ft_openredirs(t_cmd *cmdlst, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*red;

	if (!cmdlst)
		return ;
	cmd = cmdlst;
	while (cmd)
	{
		red = cmd->redirs;
		if (red)
		{
			while (red)
			{
				if (get_redir(red, shell))
					return ;
				red = red->next;
			}
		}
		cmd = cmd->next;
	}
	return ;
}

int	get_redir(t_redir *red, t_shell *shell)
{
	char	*filename;
	
	(void)shell;
	if (red->type == REDIR_APPEND)
		red->fd = open(red->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (red->type == REDIR_IN)
		red->fd = open(red->file, O_RDONLY, 0644);
	else if (red->type == REDIR_OUT)
		red->fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red->type == REDIR_HERE)
	{
		filename = gen_filename();
		red->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (red->fd < 0)
		{
			free(filename);
			return (1);
		}
		read_into_here(red->fd, red->file);
		close(red->fd);
		red->fd = open(filename, O_RDONLY);
		unlink(filename);
		free(filename);
	}
	if (red->fd < 0)
	{
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

/// @brief generates a random filename based on /dev/urandom
/// @return the filename
static char	*gen_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*name;

	num = ft_itoa(i++);
	name = ft_strjoin(".tmp_heredoc_", num);
	free(num);
	return (name);
}
