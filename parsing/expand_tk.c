/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:19:29 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/13 19:15:35 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_removequotes(char **str);
static char	*ft_replace(char *old, t_shell *shell);
static char	*ft_newstr(char *old, t_shell *shell);

/// @brief expands the tokens when necessary
/// @param lst token list
/// @param env environment
void	ft_expand(t_token **lst, t_shell *shell)
{
	t_token	*current;
	char	*expanded;
	int		i;

	if (!lst || !shell->env)
		return ;
	i = 0;
	current = *lst;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded = ft_replace(current->value, shell);
			free(current->value);
			current->value = expanded;
			ft_removequotes(&current->value);
		}
		current = current->next;
	}
}

static void	ft_removequotes(char **str)
{
	char	*trimmed;
	int		i;
	int		j;
	int		new_len;
	char	quote_state;

	i = -1;
	new_len = 0;
	quote_state = 0;
	if (!*str)
		return ;
	while ((*str)[++i])
	{
		if ((*str)[i] != '\'' && (*str)[i] != '\"')
			new_len++;
	}
	trimmed = malloc(sizeof(char) * (new_len + 1));
	if (!trimmed)
		return ;
	i = -1;
	j = 0;
	while ((*str)[++i])
	{
		if (((*str)[i] == '\'' || (*str)[i] == '\"') && quote_state == 0)
			quote_state = (*str)[i];
		else if ((*str)[i] == quote_state)
			quote_state = 0;
		else
			trimmed[j++] = (*str)[i];
	}
	trimmed[j] = '\0';
	free(*str);
	*str = trimmed;
}

static char	*ft_replace(char *old, t_shell *shell)
{
	char	*new;

	if (!old || !shell->env)
		return (NULL);
	new = ft_newstr(old, shell);
	return (new);
}

static char	*ft_newstr(char *old, t_shell *shell)
{
	char	*new;
	size_t	new_size;

	if (!old || !shell->env)
		return (NULL);
	new_size = ft_newstrsize(old, shell->env);
	new = malloc(sizeof(char) * (new_size + 1));
	if (!new)
		return (NULL);
	new[new_size] = '\0';
	ft_makenewstr(old, shell, &new);
	return (new);
}
