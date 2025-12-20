/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:20 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/17 20:36:28 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			get_redir(t_redir *red, t_shell *shell);
char		*gen_filename(void);

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

int	open_fd(t_redir *red)
{
	if (red->type == REDIR_APPEND)
		red->fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (red->type == REDIR_IN)
		red->fd = open(red->file, O_RDONLY);
	else if (red->type == REDIR_OUT)
		red->fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		red->fd = -1;
	return (red->fd);
}

int	get_redir(t_redir *red, t_shell *shell)
{
	char	*filename;

	red->fd = open_fd(red);
	if (red->type == REDIR_HERE)
	{
		filename = gen_filename();
		if (!filename)
			return (shell->exit_status = 1);
		red->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (red->fd < 0)
		{
			free(filename);
			return (shell->exit_status = 1);
		}
		read_into_here(red->fd, red->file, shell, filename);
		close(red->fd);
		red->fd = open(filename, O_RDONLY);
		unlink(filename);
		free(filename);
	}
	if (red->fd < 0)
		return (shell->exit_status = 1);
	return (0);
}

/// @brief generates a random filename based on /dev/urandom
/// @return the filename
char	*gen_filename(void)
{
	static int	i;
	char		*num;
	char		*name;

	i = 0;
	num = ft_itoa(i++);
	name = ft_strjoin(".tmp_heredoc_", num);
	free(num);
	return (name);
}
