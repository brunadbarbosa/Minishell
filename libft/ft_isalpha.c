/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:53:07 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/12 14:46:19 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

/*#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	printf("%d\n", (ft_isalpha(*argv[1])));
	return (0);
}*/