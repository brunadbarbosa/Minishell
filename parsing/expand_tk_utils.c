/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:04:51 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/02 20:04:44 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_newstrsize(char *old, t_env *env)
{
	int		i;
	int		var_len;
	size_t	new_size;
	char	*expansion;

	i = 0;
	var_len = 0;
	new_size = 0;
	while (old[i])
	{
		if (old[i] == '$' && old[i + 1] && \
(old[i + 1] == '_' || ft_isalnum(old[i + 1])))
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
	return (new_size);
}

void	ft_makenewstr(char *old, t_env *env, char **new)
{
	int		var_len;
	char	*expansion;
	int		i;
	int		j;

	var_len = 0;
	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '$' && old[i + 1] && \
(old[i + 1] == '_' || ft_isalnum(old[i + 1])))
		{
			expansion = ft_findexp(&old[i + 1], &var_len, env);
			if (expansion)
			{
				ft_memmove(&(*new)[j], expansion, ft_strlen(expansion));
				j += ft_strlen(expansion);
				free(expansion);
			}
			i += var_len + 1;
		}
		else
			(*new)[j++] = old[i++];
	}
}

char	*ft_findexp(char *var_start, int *var_len, t_env *env)
{
	t_env	*node;
	int		i;

	if (!var_start || !env)
		return (ft_strdup(""));
	*var_len = 0;
	i = 0;
	while (var_start[*var_len] && \
(ft_isalnum(var_start[*var_len]) || var_start[*var_len] == '_'))
		(*var_len)++;
	if (*var_len == 0)
		return (ft_strdup(""));
	node = env;
	while (node)
	{
		i = 0;
		while (i < *var_len && var_start[i] && \
node->name[i] && var_start[i] == node->name[i])
			i++;
		if (i == *var_len && node->name[i] == '\0')
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (ft_strdup(""));
}
