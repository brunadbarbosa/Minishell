/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:40:24 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/20 15:44:19 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_syntax(t_shell *shell)
{
	t_token	*tk;

	if (!shell || !shell->tokens)
		return ;
	tk = shell->tokens;
	if (tk->type != 0 && tk->type != 2 && tk->type != 5)
	{
		ft_clean_shell(shell, "Invalid syntax\n");
		return ;
	}
	while (tk)
	{
		if (tk->type > 0 && tk->type < 6)
		{
			if (!tk->next || tk->next->type != TOKEN_WORD)
			{
				ft_clean_tokens(&shell->tokens, "Invalid syntax\n");
				return ;
			}
		}
		tk = tk->next;
	}
}
