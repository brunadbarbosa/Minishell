/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:00:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/09/03 15:20:12 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_stash(char *buffer, char *line, int fd)
{
	ssize_t	b_read;

	ft_memmoves(buffer);
	while (1)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
		{
			if (line)
				free (line);
			return (NULL);
		}
		if (b_read == 0)
			break ;
		line = ft_strjoin_free(line, buffer);
		if (!line)
			return (NULL);
		if (ft_strchrs(buffer) >= 0)
			break ;
		ft_memmoves(buffer);
	}
	return (line);
}

char	*handle_nl(char *buffer, char *line)
{
	int		i;
	char	*final_line;
	int		nl_index;

	nl_index = ft_strchrs(line);
	if (nl_index >= 0)
	{
		i = -1;
		final_line = malloc((nl_index + 2) * sizeof(char));
		if (!final_line)
		{
			free (line);
			return (NULL);
		}
		while (++i < (nl_index + 1) && line[i])
			final_line[i] = line[i];
		final_line[nl_index + 1] = '\0';
	}
	else
		final_line = line;
	ft_memmoves(buffer);
	if (nl_index >= 0)
		free(line);
	return (final_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (buffer[0] != '\0')
		line = ft_strjoin_free(line, buffer);
	if (ft_strchrs(buffer) >= 0)
		return (handle_nl(buffer, line));
	line = read_stash(buffer, line, fd);
	line = handle_nl(buffer, line);
	return (line);
}
