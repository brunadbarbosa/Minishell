/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:43:14 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/26 17:36:31 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_int(char *args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
		return (0);
	if (args[i] == '+' || args[i] == '-')
		i++;
	while (args[i])
	{
		if (args[i] < '0' || args[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	my_exit(char **args, char *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd, "exit", 4) == 0)
	{
		printf("exit\n");
		if (!args[0])
		{
			shell->exit_status = 0;
			exit(shell->exit_status);
		}
		else if (!is_int(args[0]))
		{
			printf("minishell: exit: %s: numeric argument required.\n", args[0]);
			shell->exit_status = 255;
			exit(shell->exit_status);
		}
		else if (args[1])
		{
			printf("minishell: exit: too many arguments.\n");
			shell->exit_status = 1;
			return ;
		}
		shell->exit_status = ft_atoi(args[0]) % 256;
		exit(shell->exit_status);		
	}
}