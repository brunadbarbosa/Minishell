/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:24:19 by brmaria-          #+#    #+#             */
/*   Updated: 2025/09/17 11:07:13 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_puthex(unsigned long int n, int cas)
{
	char	*base;
	int		i;

	i = 0;
	if (cas)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n > 15)
		i = i + ft_puthex((n / 16), cas);
	i = i + ft_putchar(base[n % 16]);
	return (i);
}

int	ft_putptr(void *s)
{
	if (!s)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x") + ft_puthex((unsigned long)s, 0));
}

int	ft_putnbr(long int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		i += ft_putchar('-');
		n = n * (-1);
	}
	if (n > 9)
		i += ft_putnbr(n / 10);
	i += ft_putchar((n % 10) + 48);
	return (i);
}

int	ft_putstr(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[++i])
		ft_putchar(s[i]);
	return (i);
}
