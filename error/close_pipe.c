/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:42:22 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/24 15:42:41 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief closes open fd's from pipe if they're open and sets them to -1.
/// @param str to be passed to STDERR_FILENO in case of error.
void	ft_closepipe(int fd1, int fd2, char *str)
{
	if (fd1 >= 0)
	{
		close(fd1);
		fd1 = -1;
	}
	if (fd2 >= 0)
	{
		close(fd2);
		fd2 = -1;
	}
	if (str)
		ft_putstr_fd(str, 2);
}
