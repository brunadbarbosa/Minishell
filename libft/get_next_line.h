/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:54:41 by brmaria-          #+#    #+#             */
/*   Updated: 2025/07/30 14:06:12 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*handle_nl(char *buffer, char *line);
char	*read_stash(char *buffer, char *line, int fd);
char	*ft_strjoin_free(char *line, char *buffer);
void	ft_memmoves(char *buffer);
ssize_t	ft_strchrs(char *s);
size_t	ft_strlens(char *c);

#endif