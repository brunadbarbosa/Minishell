/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startproc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:47:40 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/27 19:56:18 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		init_pipe(t_pipe *pipe, t_cmd *cmds);
static void		ft_wait(t_pipe *pipe);
static int		ft_redcmd(int type, int fd);
static int		ft_dup2close(int pipefd, int stdfd);
static void		ft_freepipe_st(t_pipe *pipe_st);

/// @brief starts the processes and waits on them
/*
put pipefd[2] inside pipe_st. When initializing pipe_st, put the two allocations in a helper function
maybe put prev_read_fd inside the struct as well

child and parent processes can be different functions
*/
void	ft_startproc(t_shell *shell)
{
	t_pipe	pipe_st;
	t_cmd	*cmd;
	int		pipefd[2];
	int		prev_read_fd;

	if (!shell || !shell->cmds || !shell->env)
		return ;
	if(init_pipe(&pipe_st, shell->cmds))
		return (ft_putstr_fd("Unable to initialize t_pipe pipe\n", 2));
	cmd = shell->cmds;
	prev_read_fd = -1;
	while(cmd)
	{
		if (cmd->next && (pipe(pipefd) == -1))
			return (ft_freepipe_st(&pipe_st));
		pipe_st.pids[pipe_st.pid_count] = fork();
		if (pipe_st.pids[pipe_st.pid_count] == 0)
		{
			if (prev_read_fd != -1)
			{
				if (ft_dup2close(prev_read_fd, STDIN_FILENO))
					return ft_freepipe_st(&pipe_st);
			}
			if (cmd->next)
			{
				close(pipefd[0]);
				if (ft_dup2close(pipefd[1], STDOUT_FILENO))
					return ft_freepipe_st(&pipe_st);
			}
			while (cmd->redirs)
			{
				if (ft_redcmd(cmd->redirs->type, cmd->redirs->fd))
					return ft_freepipe_st(&pipe_st);
				cmd->redirs = cmd->redirs->next;
			}
			ft_freepipe_st(&pipe_st);
			ft_execute(cmd, shell->env, shell);
			ft_clean_shell(shell, NULL);
			exit (1);
		}
		if (prev_read_fd != -1)
			close(prev_read_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_read_fd = pipefd[0];
		}
		pipe_st.pid_count++;
		cmd = cmd->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	ft_wait(&pipe_st);
}

/// @brief initializes the t_pipe struct
/// @param pipe the pipe struct to be initialized
/// @param cmds the list of commands from t_shell
/// @return 0 on sucess, greater on failure
static int	init_pipe(t_pipe *pipe, t_cmd *cmds)
{
	int		node_counter;
	int		here_counter;
	t_cmd	*node;
	int		i;

	pipe->pid_count = 0;
	node_counter = 0;
	here_counter = 0;
	node = cmds;
	while (node)
	{
		node_counter++;
		if (node->redirs && node->redirs->type == REDIR_HERE)
			here_counter++;
		node = node->next;
	}
	pipe->pids = malloc(sizeof(pid_t) * node_counter);
	if (!pipe->pids)
		return (1);
	pipe->heredocs = malloc(sizeof(char *) * (here_counter + 1));
	if (!pipe->heredocs)
		return (free(pipe->pids), 2);
	i = 0;
	while (i <= here_counter)
		pipe->heredocs[i++] = NULL;
	return (0);
}

/// @brief waits on the child processes to be finished
static void	ft_wait(t_pipe *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->pid_count)
	{
		waitpid(pipe->pids[i], NULL, 0);
		i++;
	}
	free(pipe->pids);
	if (pipe->heredocs)
	{
		i = 0;
		while (pipe->heredocs[i])
		{
			unlink(pipe->heredocs[i]);
			free(pipe->heredocs[i]);
			i++;
		}
		free(pipe->heredocs);
	}
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
static int		ft_dup2close(int pipefd, int stdfd)
{
	int	i;

	i = dup2(pipefd, stdfd);
	if (i == -1)
		return (1);
	close(pipefd);
	return (0);
}

static void		ft_freepipe_st(t_pipe *pipe_st)
{
	int	i;

	if (!pipe_st)
		return ;
	free(pipe_st->pids);
	i = 0;
	while (pipe_st->heredocs[i])
	{
		free(pipe_st->heredocs[i]);
		i++;
	}
	free(pipe_st->heredocs);
}
