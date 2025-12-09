/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:08:56 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/09 19:12:13 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_child(t_pipe *pipe_st, t_cmd *cmd, t_shell *shell);
static int	ft_redcmd(int type, int fd);
static int	ft_dup2close(int pipefd, int stdfd);
static void	ft_close_remaining(t_cmd *cmd, t_cmd *head);

/// @brief forks parent and child processes
/// @param lst the command list
/// @param pipe_st the struct with pipe information
/// @param shell the master struct
void	ft_fork(t_cmd *lst, t_pipe *pipe_st, t_shell *shell)
{
	t_cmd	*cmd;

	if (!lst || !pipe_st)
		return ;
	cmd = lst;
	while (cmd)
	{
		if (cmd->next && (pipe(pipe_st->pipefd) == -1))
			return (ft_freepipe_st(pipe_st));
		pipe_st->pids[pipe_st->pid_count] = fork();
		if (pipe_st->pids[pipe_st->pid_count] == 0)
			ft_child(pipe_st, cmd, shell);
		if (pipe_st->prev_read_fd != -1)
			close(pipe_st->prev_read_fd);
		if (cmd->next)
		{
			close(pipe_st->pipefd[1]);
			pipe_st->prev_read_fd = pipe_st->pipefd[0];
		}
		pipe_st->pid_count++;
		cmd = cmd->next;
	}
}

/// @brief Structures the pipes in the child process and call ft_execute
/// @param pipe_st the pipe struct
/// @param cmd the command node
/// @param shell the master struct
static void	ft_child(t_pipe *pipe_st, t_cmd *cmd, t_shell *shell)
{
	if (!pipe_st || !cmd || !shell)
		exit (1);
	if (pipe_st->prev_read_fd != -1)
	{
		if (ft_dup2close(pipe_st->prev_read_fd, STDIN_FILENO))
			return (ft_freepipe_st(pipe_st));
	}
	if (cmd->next)
	{
		close(pipe_st->pipefd[0]);
		if (ft_dup2close(pipe_st->pipefd[1], STDOUT_FILENO))
			return (ft_freepipe_st(pipe_st));
	}
	while (cmd->redirs)
	{
		if (ft_redcmd(cmd->redirs->type, cmd->redirs->fd))
			return (ft_freepipe_st(pipe_st));
		cmd->redirs = cmd->redirs->next;
	}
	ft_freepipe_st(pipe_st);
	ft_close_remaining(cmd, shell->cmds);
	ft_execute(cmd, shell->env, shell);
	ft_clean_shell(shell, NULL);
	exit (1);
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

/// @brief calls dup2 and closes the pipe end
/// @param pipefd the end to be duplicated and then closed
/// @param stdfd STD_FILENO
/// @return 0 on success, greater on error
static int	ft_dup2close(int pipefd, int stdfd)
{
	int	i;

	i = dup2(pipefd, stdfd);
	if (i == -1)
		return (1);
	close(pipefd);
	return (0);
}

static void	ft_close_remaining(t_cmd *cmd, t_cmd *head)
{
	t_cmd	*node;
	t_cmd	*lst;

	if (!cmd || !head)
		return ;
	node = cmd;
	lst = head;
	while (lst)
	{
		if (lst != node)
			while (lst->redirs)
			{
				close (lst->redirs->fd);
				lst->redirs = lst->redirs->next;
			}
		lst = lst->next;
	}
}
