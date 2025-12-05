/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:12:42 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/05 18:15:36 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief check my option -n
/// @param args check if argument is a -n
/// @return positive if it is -n
static int	ft_checkflag(char *args)
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
/// @brief will print what was writen on the terminal
/// @param args the arguments from terminal
void	ft_echo(char **args, t_shell *shell)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (!args[i])
	{
		printf("\n");
		shell->exit_status = 0;
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
	shell->exit_status = 0;
}
