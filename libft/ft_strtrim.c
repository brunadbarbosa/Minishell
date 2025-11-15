/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:23:03 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/16 15:44:55 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	int		i;
	char	*ns;

	start = 0;
	i = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && to_trim(s1[start], set))
		start++;
	while (end > start && to_trim(s1[end], set))
		end--;
	ns = ft_calloc((end - start + 2), sizeof(char));
	if (!ns)
		return (NULL);
	while (start <= end)
		ns[i++] = s1[start++];
	return (ns);
}

/*int	main(void)
{
	char	s1[] = "+_+_+_+_+_+_+_+_42+_+_+_Porto+_+_+_+_";
	char	set[] = "+_";
	char	*ns = ft_strtrim(s1, set);
	printf("Esse seria o valor novo: %s\n", ns);
	free(ns);
	return (0);
}*/
