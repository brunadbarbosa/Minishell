/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:33:02 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/16 18:35:42 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int heredoc_child(int write_fd, char *delimiter)
{
    char *input;

    signal(SIGINT, SIG_DFL);
    while (1)
    {
        input = readline("here_doc> ");
        if (!input || strcmp(input, delimiter) == 0)
        {
            free(input);
            break ;
        }
        write(write_fd, input, ft_strlen(input));
        write(write_fd, "\n", 1);
        free(input);
    }
    close(write_fd);
    exit(0);
}

static int copy_to_file(int read_fd, int file_fd)
{
    char buf;

    while (read(read_fd, &buf, 1) > 0)
        write(file_fd, &buf, 1);
    close(read_fd);
    return (0);
}

void	read_into_here(int fd, char *delimiter)
{
    int     pipefd[2];
    pid_t   pid;
    int     status;

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
        heredoc_child(pipefd[1], delimiter);
    close(pipefd[1]);
    waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		write(STDOUT_FILENO, "\n", 1);
		g_exit_status = 130;
		return ;
	}
	copy_to_file(pipefd[0], fd);
}
