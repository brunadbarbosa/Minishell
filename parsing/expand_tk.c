/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:19:29 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/01 18:09:51 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void static	ft_replace(char **str, t_env *env);
void static	ft_removequotes(char **str, char *set);

/// @brief expands the tokens when necessary
/// @param lst token list
/// @param env environment
void	ft_expand(t_token **lst, t_env *env)
{
	t_token	*current;
	t_env	*var;

	if (!lst || !env)
		return ;
	current = *lst;
	var = env;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			if (current->value[0] == '\'')
				ft_removequotes(&current->value, "\'");
			else if (current->value[0] == '\"')
			{
				ft_removequotes(&current->value, "\"");
				ft_replace(&current->value, var);
			}
			else if (current->value[0] == '$' && current->value[1] != '?')
				ft_replace(&current->value, var);
		}
		current = current->next;
	}
}

/// @brief replaces the str with the expanded value
void static	ft_replace(char **str, t_env *env)
{
	t_env	*current;
	int		len;
	char	*clean_name;

	if (!str || !env || *str[0] != '$')
		return ;
	current = env;
	clean_name = ft_strtrim(*str, "$");
	if (!clean_name)
		return ;
	while (current)
	{
		len = ft_strlen(current->name);
		if (!ft_strncmp(clean_name, current->name, len))
		{
			free(*str);
			*str = ft_strdup(current->value);
			free(clean_name);
			return ;
		}
		current = current->next;
	}
}

void static	ft_removequotes(char **str, char *set)
{
	char	*trimmed;

	if (!*str || !set)
		return ;
	trimmed = ft_strtrim(*str, set);
	free(*str);
	*str = trimmed;
}
