/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:02:53 by brmaria-          #+#    #+#             */
/*   Updated: 2025/07/21 19:07:48 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			if (((unsigned char *)s)[i] == (unsigned char)c)
				return ((void *)&((unsigned char *)s)[i]);
			i++;
		}
	}
	return (NULL);
}

/*#include <stdio.h>
int main () {
   const char str[] = "42_common_core";
   const char c1 = 'c';
   char *r;
   r = ft_memchr(str, c1, 4);
   printf("A procura por %c e: %s\n", c1, r);
   r = ft_memchr(str, c1, 2);
   printf("A procura por %c e: %s\n", c1, r);
   return(0);
}*/