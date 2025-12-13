/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:08:56 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/13 20:09:16 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_child(t_pipe *pipe_st, t_cmd *cmd, t_shell *shell);
static int	ft_dup2close(int pipefd, int stdfd);

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
		if (pipe_st->pids[pipe_st->pid_count] == -1)
			return (ft_freepipe_st(pipe_st));
		if (pipe_st->pids[pipe_st->pid_count] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ft_child(pipe_st, cmd, shell);
		}
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
	t_redir	*redir;

	if (!pipe_st || !cmd || !shell)
		exit(1);
	if (pipe_st->prev_read_fd != -1)
	{
		if (ft_dup2close(pipe_st->prev_read_fd, STDIN_FILENO))
		{
			ft_freepipe_st(pipe_st);
			ft_clean_shell(shell, NULL);
			exit(1);
		}
	}
	if (cmd->next)
	{
		close(pipe_st->pipefd[0]);
		if (ft_dup2close(pipe_st->pipefd[1], STDOUT_FILENO))
		{
			ft_freepipe_st(pipe_st);
			ft_clean_shell(shell, NULL);
			exit(1);
		}
	}
	redir = cmd->redirs;
	while (redir)
	{
		if (ft_redcmd(redir->type, redir->fd))
		{
			ft_freepipe_st(pipe_st);
			ft_clean_shell(shell, NULL);
			exit(1);
		}
		redir = redir->next;
	}
	ft_freepipe_st(pipe_st);
	if (is_builtin(cmd))
	{
		execute_builtin(cmd, shell);
		ft_clean_shell(shell, NULL);
		exit(shell->exit_status);
	}
	ft_execute(cmd, shell->env, shell);
	ft_clean_shell(shell, NULL);
	exit(127);
}

/// @brief redirects command to its infile and outfile
/// @param type the redirection type
/// @param fd the file descriptor of the redirection file
/// @return 0 on success, greater then 0 on failure
int	ft_redcmd(int type, int fd)
{
	if (type == REDIR_IN || type == REDIR_HERE)
	{
		if ((dup2(fd, STDIN_FILENO)) == -1)
		{
			close(fd);
			ft_putstr_fd(" No such file or directory\n", 2);
			return (1);
		}
		close(fd);
	}
	else if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		if ((dup2(fd, STDOUT_FILENO)) == -1)
		{
			close(fd);
			ft_putstr_fd(" Permission denied\n", 2);
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
