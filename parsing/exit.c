/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:07:07 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/28 18:59:27 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_shell *shell, char *input)
{
	size_t	len;

	len = ft_strlen(input);
	if (len == 0)
		return ;
	if (!ft_strncmp(input, "out", 4))
	{
		free(input);
		ft_clean_shell(shell, NULL);
		exit(EXIT_SUCCESS);
	}
}
