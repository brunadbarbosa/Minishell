/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:31:15 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 18:29:13 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digits(int nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
	{
		count++;
		nbr = nbr * (-1);
	}
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*m;
	int			i;
	long int	nb;

	nb = n;
	i = ft_count_digits(nb);
	m = ft_calloc((i + 1), sizeof(char));
	if (!m)
		return (0);
	if (nb == 0)
		m[0] = '0';
	if (nb < 0)
	{
		m[0] = '-';
		nb = nb * (-1);
	}
	while (nb > 0)
	{
		m[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	return (m);
}

/*#include <stdio.h>
int	main(void)
{
	int nb = -37;

	printf("%s\n", ft_itoa(nb));
	return (0);
}*/