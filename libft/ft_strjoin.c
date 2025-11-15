/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:01:21 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/17 11:54:10 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	counts1;
	size_t	counts2;
	char	*ns;

	counts1 = ft_strlen(s1);
	counts2 = ft_strlen(s2);
	ns = ft_calloc((counts1 + counts2 + 1), sizeof(char));
	if (!ns)
		return (0);
	ft_strlcpy(ns, s1, (counts1 + 1));
	ft_strlcat(ns, s2, (counts1 + counts2 + 1));
	return (ns);
}

/*int	main (int argc, char **argv)
{
	if (argc != 3)
		return (-1);
	printf("%s\n", ft_strjoin(argv[1], argv[2]));
	return (0);
}*/