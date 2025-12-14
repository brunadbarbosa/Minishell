/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:19:29 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/14 19:26:15 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_removequotes(char **str);
static char	*ft_newstr(char *old, t_shell *shell);

/// @brief expands the tokens when necessary
/// @param lst token list
/// @param env environment
void	ft_expand(t_token **lst, t_shell *shell)
{
	t_token	*current;
	char	*expanded;

	if (!lst || !shell->env)
		return ;
	current = *lst;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded = ft_newstr(current->value, shell);
			free(current->value);
			current->value = expanded;
			ft_removequotes(&current->value);
		}
		current = current->next;
	}
}

static int	count_content(char *str)
{
	int		i;
	int		count;
	char	quote_state;

	i = 0;
	count = 0;
	quote_state = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote_state == 0)
			quote_state = str[i];
		else if (str[i] == quote_state)
			quote_state = 0;
		else
			count++;
		i++;
	}
	return (count);
}

static void	copy_without_quotes(char *src, char *dst)
{
	int		i;
	int		j;
	char	quote_state;

	i = 0;
	j = 0;
	quote_state = 0;
	while (src[i])
	{
		if ((src[i] == '\'' || src[i] == '"') && quote_state == 0)
			quote_state = src[i];
		else if (src[i] == quote_state)
			quote_state = 0;
		else
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
}

static void	ft_removequotes(char **str)
{
	char	*trimmed;
	int		new_len;

	if (!*str)
		return ;
	new_len = count_content(*str);
	trimmed = malloc(sizeof(char) * (new_len + 1));
	if (!trimmed)
		return ;
	copy_without_quotes(*str, trimmed);
	free(*str);
	*str = trimmed;
}

static char	*ft_newstr(char *old, t_shell *shell)
{
	char	*new;
	size_t	new_size;

	if (!old || !shell->env)
		return (NULL);
	new_size = ft_newstrsize(old, shell);
	new = malloc(sizeof(char) * (new_size + 1));
	if (!new)
		return (NULL);
	new[new_size] = '\0';
	ft_makenewstr(old, shell, &new);
	return (new);
}
