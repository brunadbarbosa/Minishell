/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:45:55 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/12 12:06:10 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size > 0)
	{
		while (dst[j] != '\0' && j < size)
			j++;
		if (j < size)
		{
			while (src[i] != '\0' && (j + i) < (size - 1))
			{
				dst[j + i] = src[i];
				i++;
			}
			dst[j + i] = '\0';
		}
	}
	return (j + ft_strlen((char *)src));
}

/*int	main(void)
{
	char dst[20] = "Hello";
	const char *src = " World";

	printf("Antes: %s\n", dst);
	printf("Depois: %zu\n", strlcat(dst, src, 3));	
	return 0;
}*/