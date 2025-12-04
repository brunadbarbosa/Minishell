/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:parsing/exit.c
/*   Created: 2025/11/18 19:07:07 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/28 18:59:27 by adpinhei         ###   ########.fr       */
=======
/*   Created: 2025/11/08 17:59:27 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/30 17:58:24 by brmaria-         ###   ########.fr       */
>>>>>>> 34c332dfdc4124a4b0ad3bfa44fb57c5539ee2ad:builtins/env.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

 
/// @brief Will print all env's list
/// @param env to be printed
void	ft_env(t_env *env)
{
<<<<<<< HEAD:parsing/exit.c
	size_t	len;

	len = ft_strlen(input);
	if (len == 0)
		return ;
	if (!ft_strncmp(input, "out", 4))
=======
	while (env)
>>>>>>> 34c332dfdc4124a4b0ad3bfa44fb57c5539ee2ad:builtins/env.c
	{
		if (env->value && env->value[0])
		{
			printf("%s=", env->name);
			printf("%s", env->value);	
			printf("\n");
		}
			env = env->next;
	}
}
