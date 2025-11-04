/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:02:26 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/30 17:39:11 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	dest = (char *)malloc((length + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s, (length + 1));
	return (dest);
}
