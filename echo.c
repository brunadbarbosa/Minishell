/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:12:42 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/09 15:55:33 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_checkflag(char *args)
{
	int	i;

	i = 0;
	if (!args || args[0] != '-')
		return (0);
	i++;
	while(args[i])
	{
		if (args[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_echo(char **args)
{
	int	i;
	int	sign;

	i = 1;
	sign = 0;
	if (!args[i])
	{
		printf("\n");
		return ;		
	}
	if (ft_checkflag(args[i]))
	{
		i++;
		sign = 1;		
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (sign == 0)
		printf("\n");
}


int	main(void)
{
	char *cmd1[] = {"echo", "Hello", "world!", NULL};
	char *cmd2[] = {"echo", "-n-n-n-n-n-n", "Sem", "nova", "linha", NULL};
	char *cmd3[] = {"echo", NULL};

	printf("Teste 1:\n");
	ft_echo(cmd1);
	printf("Teste 2:\n");
	ft_echo(cmd2);
	printf("Teste 3:\n");
	ft_echo(cmd3);

	return (0);
}
