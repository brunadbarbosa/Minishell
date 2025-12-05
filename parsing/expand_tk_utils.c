/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:04:51 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/05 17:23:54 by brmaria-         ###   ########.fr       */
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

void	ft_makenewstr(char *old, t_shell *shell, char **new)
{
	int     var_len;
    char    *expansion;
    int     i;
    int     j;
    char    quote_state;

    var_len = 0;
    i = 0;
    j = 0;
    quote_state = 0;
    while (old[i])
    {
        if (old[i] == '\'' || old[i] == '"')
        {
            if (quote_state == 0)
                quote_state = old[i];
            else if (quote_state == old[i])
                quote_state = 0;
        }
        if (old[i] == '$' && quote_state != '\'') 
        {

            if (old[i + 1] == '?')
            {
                expansion = ft_itoa(shell->exit_status);
                if (expansion)
                {
                    ft_memmove(&(*new)[j], expansion, ft_strlen(expansion));
                    j += ft_strlen(expansion);
                    free(expansion);
                }
                i += 2;
                continue;
            }
            else if (old[i + 1] == '_' || ft_isalnum(old[i + 1]))
            {
                expansion = ft_findexp(&old[i + 1], &var_len, shell->env);
                if (expansion)
                {
                    ft_memmove(&(*new)[j], expansion, ft_strlen(expansion));
                    j += ft_strlen(expansion);
                    free(expansion);
                }
                i += var_len + 1;
                continue;
            }
        }
        (*new)[j++] = old[i++];
    }
    (*new)[j] = '\0';
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
node->name[i] && var_start[i] == node->name[i])        // 1. RASTREAMENTO DO ESTADO DAS ASPAS
			i++;
		if (i == *var_len && node->name[i] == '\0')
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (ft_strdup(""));
}
