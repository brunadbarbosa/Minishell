/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:40:14 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/12 11:58:33 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*#include <stdio.h>
int	main(void)
{
	char str[] = "abchfkgjdef";

   ft_bzero(str, 2);
   for (int i = 0; i < 11; i++)
		printf("str[%d] = 0x%x (%c)\n", i, str[i], str[i]);
   return 0;
}*/