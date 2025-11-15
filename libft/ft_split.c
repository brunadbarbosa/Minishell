/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:53:14 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/20 14:28:56 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(const char *s1, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (c == '\0')
		return (1);
	while (s1[i])
	{
		if (s1[i] != c && (i == 0 || s1[i -1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_free(char **split, int i)
{
	while (i >= 0)
		free(split[i--]);
	free(split);
	return (NULL);
}

char	*ft_fill(int start, const char *s, int count)
{
	char	*str;

	str = ft_calloc(count + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start - count, count + 1);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i[3];
	char	**split;

	split = ft_calloc(ft_word_count((char *)s, c) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i[1] = -1;
	i[0] = 0;
	while (s[i[0]])
	{
		while (s[i[0]] == c)
			i[0]++;
		if (!s[i[0]])
			break ;
		i[2] = 0;
		while (s[i[0]] != c && s[i[0]])
		{
			i[2]++;
			i[0]++;
		}
		split[++i[1]] = ft_fill(i[0], s, i[2]);
		if (!split[i[1]])
			return (ft_free(split, i[1]));
	}
	return (split);
}
