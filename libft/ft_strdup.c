/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:46:54 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/12 12:05:21 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t			count;
	char			*d;

	count = 0;
	d = malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	while (s[count] != '\0')
	{
		d[count] = s[count];
		count++;
	}
	d[count] = '\0';
	return (d);
}

/*int	main (int argc, char **argv)
{
	if (argc != 2)
		return -1;
	char	*dup = 	ft_strdup(argv[1]);
	printf("%s\n", dup);
	free(dup);
	return(0);
}*/