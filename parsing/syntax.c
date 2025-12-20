/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:40:24 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 18:35:06 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_syntax(t_shell *shell)
{
	t_token	*tk;

	if (!shell || !shell->tokens)
		return ;
	tk = shell->tokens;
	if (tk->type == TOKEN_PIPE)
	{
		ft_clean_tokens(&shell->tokens, "Invalid syntax\n");
		return ;
	}
	while (tk)
	{
		if (tk->type > TOKEN_WORD)
		{
			if (!tk->next || tk->next->type != TOKEN_WORD)
				return (ft_clean_tokens(&shell->tokens, "Invalid syntax\n"));
		}
		if (tk->type != TOKEN_WORD && !tk->next)
			return (ft_clean_tokens(&shell->tokens, "Invalid syntax\n"));
		tk = tk->next;
	}
}
