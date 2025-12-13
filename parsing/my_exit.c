/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:39:41 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/13 19:39:52 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_exit(t_shell *shell, char *input)
{
	size_t	len;

	len = ft_strlen(input);
	if (len == 0)
		return ;
	if (!ft_strncmp(input, "exit", 5))
	{
		free(input);
		ft_clean_shell(shell, NULL);
		exit(EXIT_SUCCESS);
	}
}
