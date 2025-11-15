/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:49:57 by brmaria-          #+#    #+#             */
/*   Updated: 2025/04/19 13:46:56 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/*#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *str = "Zedro";
	t_list *strlist = NULL;
	strlist = ft_lstnew(str);
	printf("%s\n",(char *)strlist->content);
	int nbr = 42;
	t_list *intlist = NULL;
	intlist = ft_lstnew(&nbr);
	printf("%d\n", *(int *)intlist->content);
	free (intlist);
	free (strlist);
	return (0);
}*/