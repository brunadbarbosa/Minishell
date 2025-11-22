/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:09:43 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/22 19:12:53 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"



void	ft_cd(char **args, t_env **env)
{
	char	old_pwd;
	char	pwd;
	char	target_pwd;
	int		result;
	
	if (!args)
		return (1);
	old_pwd = get_from_env("OLDPWD", env);
	pwd = get_from_env("PATH", env);
	result = chdir(target_pwd);
	if (result == -1)
	{
		//error message
		//free o que for necessario
		return (1);
	}
}