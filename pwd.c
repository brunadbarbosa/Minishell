/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:31:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/08 17:28:11 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char *getpwd(char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if (!strncmp(envp[i], "PWD=", 4))
			return (strdup(envp[i] + 4));
		i++;
	}
	return (NULL);
}

int	ft_pwd(char **envp)
{
	char	*dir;
	
	dir = getpwd(envp);
	printf("%s\n", dir);
	return (0);
}
