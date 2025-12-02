/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:19:29 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/02 20:04:35 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_removequotes(char **str, char *set);
static char	*ft_replace(char *old, t_env *env);
static char	*ft_newstr(char *old, t_env *env);

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
			else
			{
				if (current->value[0] == '\"')
					ft_removequotes(&current->value, "\"");
				expanded = ft_replace(current->value, env);
				free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
}

static void	ft_removequotes(char **str, char *set)
{
	char	*trimmed;

	if (!*str || !set)
		return ;
	trimmed = ft_strtrim(*str, set);
	free(*str);
	*str = trimmed;
}

static char	*ft_replace(char *old, t_env *env)
{
	char	*new;

	if (!old || !env)
		return (NULL);
	new = ft_newstr(old, env);
	return (new);
}

static char	*ft_newstr(char *old, t_env *env)
{
	char	*new;
	size_t	new_size;

	if (!old || !env)
		return (NULL);
	new_size = ft_newstrsize(old, env);
	new = malloc(sizeof(char) * (new_size + 1));
	if (!new)
		return (NULL);
	new[new_size] = '\0';
	ft_makenewstr(old, env, &new);
	return (new);
}
