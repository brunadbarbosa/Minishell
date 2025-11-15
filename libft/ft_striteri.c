/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:28:43 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 14:59:49 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// static void	ft_maximize(unsigned int i, char *c)
// {
// 	(void)i;
// 	if (*c > 96 && *c < 123)
// 		*c -= 32;
// 	return ;
// }

// int	main(void)
// {
// 	char s[] = "42_coMmon_core";

// 	ft_striteri(s, ft_maximize);
// 	printf("Capitalized: %s\n", s);
// 	return (0);
// }