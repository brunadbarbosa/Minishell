/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:19:03 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/20 18:36:41 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_overflow(long long result, int sign, int digit)
{
	if (sign == 1)
	{
		if (result > LLONG_MAX / 10
			|| (result == LLONG_MAX / 10
				&& digit > LLONG_MAX % 10))
			return (1);
	}
	else
	{
		if (result > -(LLONG_MIN / 10)
			|| (result == -(LLONG_MIN / 10)
				&& digit > -(LLONG_MIN % 10)))
			return (1);
	}
	return (0);
}

int	convert_digits(const char *str, int *i, long long *result, int sign)
{
	while (str[*i])
	{
		if (str[*i] < '0' || str[*i] > '9'
			|| check_overflow(*result, sign, str[*i] - '0'))
			return (0);
		*result = *result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (1);
}

int	safe_atoll(const char *str, long long *out)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (ft_strncmp(str, "--", ft_strlen(str)) == 0)
	{
		*out = 0;
		return (1);
	}
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	if (!convert_digits(str, &i, &result, sign))
		return (0);
	return (*out = result * sign);
}

int	check_too_many_args(char **args, t_shell *shell)
{
	if (args[1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	ft_exit(char **args, char *cmd, t_shell *shell)
{
	long long	val;

	if (ft_strncmp(cmd, "exit", 4) == 0)
	{
		printf("exit\n");
		if (!args[0])
		{
			val = shell->exit_status;
			ft_clean_shell(shell, NULL);
			exit(val);
		}
		if (!safe_atoll(args[0], &val))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_clean_shell(shell, NULL);
			exit(2);
		}
		if (check_too_many_args(args, shell))
			return ;
		shell->exit_status = val % 256;
		ft_clean_shell(shell, NULL);
		exit((unsigned char)val);
	}
}
