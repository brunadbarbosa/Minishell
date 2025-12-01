/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:19:29 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/01 20:40:50 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void static	ft_removequotes(char **str, char *set);

/// @brief expands the tokens when necessary
/// @param lst token list
/// @param env environment
void	ft_expand(t_token **lst, t_env *env)
{
	t_token	*current;
	char	*expanded;

	if (!lst || !env)
		return ;
	current = *lst;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			if (current->value[0] == '\'')
				ft_removequotes(&current->value, "\'");
			else if (current->value[0] == '\"')
			{
				ft_removequotes(&current->value, "\"");
				ft_replace(current->value, &expanded, env);
			}
			else
			{
				ft_replace(&current->value, &expanded, env);
				current->value = expanded;
			}
		}
		current = current->next;
	}
}

/// @brief trims quotes from token->value
/// @param str the string to be trimmed
/// @param set the quotes to be removed
void static	ft_removequotes(char **str, char *set)
{
	char	*trimmed;

	if (!*str || !set)
		return ;
	trimmed = ft_strtrim(*str, set);
	free(*str);
	*str = trimmed;
}

static void	ft_replace(char **old, char **new, t_env *env)
{
	if (!env || !old || !*old)
		return ;
	
}