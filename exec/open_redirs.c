/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:20 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/08 18:49:57 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_redir(t_redir *red);
static char	*gen_filename(void);

/// @brief iterates through the command list to find redirections
/// @param cmdlst the list of commands
/// @param shell the master struct
void	ft_openredirs(t_cmd *cmdlst)
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
				get_redir(red);
				red = red->next;
			}
		}
		cmd = cmd->next;
	}
}

/// @brief gets the file descriptors for the redirections
/// @param red the t_redir struct with redirection info
static void	get_redir(t_redir *red)
{
	char	*filename;

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
			return (free(filename));
		read_into_here(red->fd, red->file);
		close(red->fd);
		red->fd = open(filename, O_RDONLY);
		unlink(filename);
		free(filename);
	}
	return ;
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
