/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:20:13 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/15 17:08:01 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_isspace(const char c)
{
	return ((c > 8 && c < 14) || c == 32);
}

bool	is_operator(const char *str)
{
	if (!str)
		return (false);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (true);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (true);
	else if (*str == '>' || *str == '<' || *str == '|' || *str == ' ')
		return (true);
	else
		return (false);
}

bool	is_quote(const char str)
{
	if (!str)
		return (false);
	else if (str == '"' || str == '\'')
		return (true);
	else
		return (false);
}

bool	is_delimiter(const char *str)
{
	if (!str)
		return (false);
	else if (is_operator(str) || ft_isspace(*str))
		return (true);
	else
		return (false);
}
