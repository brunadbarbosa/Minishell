/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:00:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 18:25:42 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	n;

	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	n = slen - start;
	if (n > len)
		n = len;
	sub = ft_calloc((n + 1), sizeof(char));
	if (!sub)
		return (0);
	ft_strlcpy(sub, (&s[start]), (n + 1));
	return (sub);
}

/*int	main(int argc, char **argv)
{
	if (argc != 4)
		return -1;
	char	*d = ft_substr(argv[1], atoi(argv[2]), atoi(argv[3]));
	printf("%s\n", d);
	free(d);
	return (0);
}*/