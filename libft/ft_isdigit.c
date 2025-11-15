/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:25:16 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/12 14:46:41 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57));
}

/*#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	printf("%d\n", (ft_isdigit(*argv[1])));
	return (0);
}*/