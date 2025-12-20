/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:14:38 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/20 18:35:31 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

static int	heredoc_child(int write_fd, char *delimiter,
		t_shell *shell, char *filename)
{
	char	*input;

	signal(SIGINT, heredoc_sigint);
	while (1)
	{
		input = readline("here_doc> ");
		if (!input || ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		write(write_fd, input, ft_strlen(input));
		write(write_fd, "\n", 1);
		free(input);
	}
	close(write_fd);
	free(filename);
	ft_clean_shell(shell, NULL);
	exit(0);
}

static int	copy_to_file(int read_fd, int file_fd)
{
	char	buf;

	while (read(read_fd, &buf, 1) > 0)
		write(file_fd, &buf, 1);
	close(read_fd);
	return (0);
}

void	read_into_here(int fd, char *delimiter, t_shell *shell, char *filename)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (fd < 0 || pipe(pipefd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	if (pid == 0)
		heredoc_child(pipefd[1], delimiter, shell, filename);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (status > 0)
	{
		close(pipefd[0]);
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	copy_to_file(pipefd[0], fd);
}
