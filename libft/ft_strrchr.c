/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:37:14 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 17:04:09 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;

	i = ft_strlen(s);
	if (!s)
		return (0);
	while (i > -1)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}

/*#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 3)
		return (-1);
	printf ("%s", ft_strrchr(argv[1], *argv[2]));
	return (0);
}*/