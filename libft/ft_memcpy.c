/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:54:17 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 16:53:58 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	if (n > 0)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/*int main() {
	char source[] = "Hello!";
	char destination[10];

	ft_memcpy(destination, source, 6);  // Copy 6 bytes (H, e, l, l, o, !)
	destination[6] = '\0';          // Make sure it ends with '\0'

	printf("destination: %s\n", destination);  // Output: Hello!
	return (0);
}*/