/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:07:18 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/12 12:08:29 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/*#include <unistd.h>
int	main (int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	char	c = ft_tolower(*argv[1]);
	write (1, &c, 1);
	return (0);
}*/