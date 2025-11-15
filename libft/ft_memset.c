/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:01:25 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/12 12:03:19 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (n > 0)
	{
		((unsigned char *)s)[n - 1] = c;
		n--;
	}
	return (s);
}

/*#include <stdio.h>
int	main(void)
{
	char str[] = ".,fjndkrgbsk";
	
   ft_memset(str, 'Z', 2);
   printf("String after memset(): %s\n", str);
   return 0;
}*/