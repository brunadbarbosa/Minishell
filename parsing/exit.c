/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:07:07 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/18 20:07:49 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_shell *shell, char *input)
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
