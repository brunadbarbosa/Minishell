/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:42:08 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/18 18:45:46 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

e_redir_type	redirtype(e_token_type type)
{
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (type == TOKEN_HEREDOC)
		return (REDIR_HERE);
	if (type == TOKEN_RED_IN)
		return (REDIR_IN);
	if (type == TOKEN_RED_OUT)
		return (REDIR_OUT);
	else
		return (-1);
}
