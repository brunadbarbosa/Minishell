/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:12:20 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 17:58:57 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*#include <fcntl.h>
int	main(void)
{
	int	fd;

	fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if (fd == -1)
		return (1);
	
	ft_putchar_fd('4', fd);
	ft_putchar_fd('2', fd);
	ft_putchar_fd('_', fd);
	ft_putchar_fd('c', fd);
	ft_putchar_fd('o', fd);
	ft_putchar_fd('m', fd);
	ft_putchar_fd('m', fd);
	ft_putchar_fd('o', fd);
	ft_putchar_fd('n', fd);
	ft_putchar_fd('_', fd);
	ft_putchar_fd('c', fd);
	ft_putchar_fd('o', fd);
	ft_putchar_fd('r', fd);
	ft_putchar_fd('e', fd);
	ft_putchar_fd('!', fd);
	ft_putchar_fd('\n', fd);
	
	close(fd);
	return (0);
}*/