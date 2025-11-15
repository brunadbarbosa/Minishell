/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:18:24 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 14:11:05 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	int	count;

	count = 0;
	while (c[count])
		count++;
	return (count);
}

/*#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	printf("%d\n", (ft_strlen(argv[1])));
	return (0);
}*/