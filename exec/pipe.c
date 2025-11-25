/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:09 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/25 11:42:09 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_redcmd(int type, int fd);
static int	ft_regpipe(t_cmd *node, t_cmd **head);

/// @brief assigns to each command their stdin and stdout based on redirs
/// @param cmdlst the list of commands
/// @return 0 on success, greater on error
int	ft_pipe(t_cmd *cmdlst)
{
	t_cmd	*cmd;

	if (!cmdlst)
		return (1);
	cmd = cmdlst;
	if (cmd)
	{
		if (cmd->redirs)
		{
			while (cmd->redirs)
			{
				if (ft_redcmd(cmd->redirs->type, cmd->redirs->fd))
					return (2) ;
				cmd->redirs = cmd->redirs->next;
			}
		}
		else
			if (ft_regpipe(cmd, &cmdlst))
				return (3);
	}
	return (0);
}

/// @brief redirects command to its infile and outfile
/// @param type the redirection type
/// @param fd the file descriptor of the redirection file
/// @return 0 on success, greater then 0 on failure
static int	ft_redcmd(int type, int fd)
{
	if (type == REDIR_IN || type == REDIR_HERE)
	{
		if ((dup2(fd, STDIN_FILENO)) == -1)
		{
			close(fd);
			ft_putstr_fd("Failed stdin at ft_redcmd\n", 2);
			return (1);
		}
		close(fd);
	}
	else if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		if ((dup2(fd, STDOUT_FILENO)) == -1)
		{
			close(fd);
			ft_putstr_fd("Failed stdout at ft_redcmd\n", 2);
			return (2);
		}
		close(fd);
	}
	return (0);
}

/// @brief makes the regular pipe, i.e. commands after '|' read from the
/// pipe, commands followed by '|' write to the pipe. 
/// @param node the current t_cmd*
/// @param head the head to the t_cmd list
/// @return 0 on success, greater otherwise
static int	ft_regpipe(t_cmd *node, t_cmd **head)
{
	t_cmd	*cmd;
	int		pipefd[2];

	if (!node || !head || !*head)
		return (4);
	if (pipe(pipefd) == -1)
		return (perror("regpipe err1"), 1);
	cmd = node;
	if (cmd != *head)
	{
		if ((dup2(pipefd[0], STDIN_FILENO)) == -1)
			return (ft_closepipe(pipefd[0], pipefd[1], "regpipe err2\n"), 2);
		close(pipefd[0]);
	}
	if (cmd->next)
	{
		if ((dup2(pipefd[1], STDOUT_FILENO)) == -1)
			return (ft_closepipe(pipefd[0], pipefd[1], "regpipe err3\n"), 3);
		close(pipefd[1]);
	}
	return (0);
}
