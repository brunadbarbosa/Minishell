/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_maker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:06:06 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/06 11:57:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief adds t_cmd to the cmd list
/// @param token the head to the token list
/// @param cmd_lst the head to the cmd list
void	ft_add_cmd(t_token *token, t_cmd *cmd_lst)
{
	if (!token)
		return ;
	while (token->type != TOKEN_EOF)
	{
		if (!cmd_lst)
			cmd_lst = ft_makecmd();
		else
		{
			while (cmd_lst->next)
				cmd_lst = cmd_lst->next;
			cmd_lst = ft_makecmd();
		}
		token = token->next;
	}
}

t_cmd	*ft_makecmd()
{
	
}