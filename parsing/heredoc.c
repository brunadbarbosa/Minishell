/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:33:02 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/08 16:08:05 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief copies t_shell->heredoc to t_pipe->heredocs
/// @param dest_here t_pipe->heredocs
/// @param src_here t_shell->heredoc
void	cpy_heredoc(char ***dest_here, char ***src_here)
{
	int	i;

	if (!src_here || !*src_here || !**src_here)
		return ;
	i = 0;
	while ((*src_here)[i])
	{
		(*dest_here)[i] = (*src_here)[i];
		i++;
	}
	(*dest_here)[i] = NULL;
}

/// @brief reads from STDIN into the heredoc file
/// @param fd the file descriptor to the heredoc file
/// @param delimiter the line defined as heredoc delimiter
void	read_into_here(int fd, char *delimiter)
{
	char	*eof;
	char	*input;

	if (fd < 0)
		return ;
	eof = ft_strjoin(delimiter, "\n");
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		input = get_next_line(STDIN_FILENO);
		if (((ft_strncmp(eof, input, ft_strlen(input))) == 0) || !input)
			break ;
		ft_putstr_fd(input, fd);
		free(input);
	}
	free(eof);
	if (input)
		free(input);
}
