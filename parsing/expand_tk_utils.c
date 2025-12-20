/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:04:51 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 18:35:37 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	calc_size(char *old, int *i, t_shell *shell, int *var_len)
{
	char	*exp;
	size_t	size;

	if (old[*i + 1] == '?')
	{
		exp = ft_itoa(shell->exit_status);
		size = ft_strlen(exp);
		free(exp);
		*i += 2;
		return (size);
	}
	exp = ft_findexp(&old[*i + 1], var_len, shell->env);
	size = ft_strlen(exp);
	free(exp);
	*i += *var_len + 1;
	return (size);
}

void	do_expand(char *old, t_shell *shell, char **new, int idx[2])
{
	char	*exp;
	int		var_len;

	if (old[idx[0] + 1] == '?')
		exp = ft_itoa(shell->exit_status);
	else
		exp = ft_findexp(&old[idx[0] + 1], &var_len, shell->env);
	if (exp)
	{
		ft_memmove(&(*new)[idx[1]], exp, ft_strlen(exp));
		idx[1] += ft_strlen(exp);
		free(exp);
	}
	if (old[idx[0] + 1] == '?')
		idx[0] += 2;
	else
		idx[0] += var_len + 1;
}

// idx[0] = i, idx[1] = j
void	ft_makenewstr(char *old, t_shell *shell, char **new)
{
	int		idx[2];
	char	quote_state;

	idx[0] = 0;
	idx[1] = 0;
	quote_state = 0;
	while (old[idx[0]])
	{
		update_quote(old[idx[0]], &quote_state);
		if (old[idx[0]] == '$' && quote_state != '\'' && old[idx[0] + 1]
			&& (old[idx[0] + 1] == '?' || old[idx[0] + 1] == '_'
				|| ft_isalnum(old[idx[0] + 1])))
		{
			do_expand(old, shell, new, idx);
			continue ;
		}
		(*new)[idx[1]++] = old[idx[0]++];
	}
	(*new)[idx[1]] = '\0';
}

size_t	ft_newstrsize(char *old, t_shell *shell)
{
	int		i;
	int		var_len;
	size_t	new_size;
	char	quote_state;

	i = 0;
	new_size = 0;
	quote_state = 0;
	while (old[i])
	{
		update_quote(old[i], &quote_state);
		if (old[i] == '$' && quote_state != '\'' && old[i + 1]
			&& (old[i + 1] == '?' || old[i + 1] == '_'
				|| ft_isalnum(old[i + 1])))
			new_size += calc_size(old, &i, shell, &var_len);
		else
		{
			new_size++;
			i++;
		}
	}
	return (new_size);
}

char	*ft_findexp(char *var_start, int *var_len, t_env *env)
{
	t_env	*node;
	int		i;

	if (!var_start || !env)
		return (ft_strdup(""));
	*var_len = 0;
	while (var_start[*var_len]
		&& (ft_isalnum(var_start[*var_len]) || var_start[*var_len] == '_'))
		(*var_len)++;
	if (*var_len == 0)
		return (ft_strdup(""));
	node = env;
	while (node)
	{
		i = 0;
		while (i < *var_len && var_start[i] && node->name[i]
			&& var_start[i] == node->name[i])
			i++;
		if (i == *var_len && node->name[i] == '\0')
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (ft_strdup(""));
}
