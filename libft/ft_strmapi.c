/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:51:01 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 15:28:25 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ns;
	int		i;

	i = 0;
	ns = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!ns)
		return (0);
	while (s[i])
	{
		ns[i] = f(i, s[i]);
		i++;
	}
	return (ns);
}

// static char	ft_maximize(unsigned int i, char c)
// {
// 	(void)i;
// 	if (c > 96 && c < 123)
// 		c -= 32;
// 	return (c);
// }

// int	main(void)
// {
// 	char *s = "42_common_core";
// 	char *capitalized;

// 	capitalized = ft_strmapi(s, ft_maximize);
// 	printf("Original: %s\n", s);
// 	printf("Capitalized: %s\n", capitalized);
// 	free(capitalized);
// 	return (0);
// }