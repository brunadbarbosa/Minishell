/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:19:29 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/02 18:58:57 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_removequotes(char **str, char *set);
static char	*ft_replace(char *old, t_env *env);
static char	*ft_newstr(char *old, t_env *env);
static char	*ft_findexp(char *var_start, int *var_len, t_env *env);

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
	char	*expansion;
	int		var_len;
	size_t	new_size;
	int		i;
	int		j;

	if (!old || !env)
		return (NULL);
	var_len = 0;
	new_size = 0;
	i = 0;
	j = 0;
	new = NULL;
	while (old[i])
	{
		if (old[i] == '$' && old[i + 1] && (old[i + 1] == '_' || ft_isalnum(old[i + 1])))
		{
			expansion = ft_findexp(&old[i + 1], &var_len, env);
			new_size += ft_strlen(expansion);
			free(expansion);
			i += var_len + 1;
		}
		else
		{
			new_size++;
			i++;
		}
	}
	new = malloc(sizeof(char) * (new_size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		if (old[i] == '$' && old[i + 1] && (old[i + 1] == '_' || ft_isalnum(old[i + 1])))
		{
			expansion = ft_findexp(&old[i + 1], &var_len, env);
			if (expansion)
			{
				ft_memmove(&new[j], expansion, ft_strlen(expansion));
				j += ft_strlen(expansion);
				free(expansion);
			}
			i += var_len + 1;
		}
		else
		{
			new[j] = old[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}

static char	*ft_findexp(char *var_start, int *var_len, t_env *env)
{
	t_env	*node;
	int		i;

	if (!var_start || !env)
		return (ft_strdup(""));
	*var_len = 0;
	i = 0;
	while (var_start[*var_len] && (ft_isalnum(var_start[*var_len]) || var_start[*var_len] == '_'))
		(*var_len)++;
	if (*var_len == 0)
		return (ft_strdup(""));
	node = env;
	while (node)
	{
		i = 0;
		while (i < *var_len && var_start[i] && node->name[i] && var_start[i] == node->name[i])
			i++;
		if (i == *var_len && node->name[i] == '\0')
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (ft_strdup(""));
}
