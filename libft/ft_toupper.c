/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:51:22 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 15:00:29 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

/*#include <unistd.h>
int	main (int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	char	c = ft_toupper(*argv[1]);
	write (1, &c, 1);
	return (0);
}*/
