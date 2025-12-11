/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:31:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/10 11:39:57 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief Gets PWD's content from env
/// @param env env's list
/// @return PWD's content
char *getpwd(t_env *env)
{
	while(env)
	{
		if (!ft_strncmp(env->name, "PWD", 3))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
/// @brief prints PWD
/// @param env env's list
void	ft_pwd(t_env *env)
{
	char	*dir;
	
	dir = getpwd(env);
	if (dir)
	{
		printf("%s\n", dir);
		free(dir);
	}
}
