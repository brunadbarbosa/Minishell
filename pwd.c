/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:31:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/23 19:43:34 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

char	*get_current_path(void)
{
	char	*cwd;
	int	size;

	size = 1024;
	cwd = malloc(size);
	if (!cwd)
	{
		perror("cd");
		return (1);
	}
	getcwd(cwd, size);
	return (cwd);
}

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
}
/// @brief prints PWD
/// @param env env's list
void	ft_pwd(t_env *env)
{
	char	*dir;
	
	dir = getpwd(env);
	printf("%s\n", dir);
}
