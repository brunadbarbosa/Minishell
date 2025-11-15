/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:19:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/15 16:25:16 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	
	env = init_env_list(envp);
	(void)argc;
	if (strcmp(argv[1], "pwd") == 0)
		ft_pwd(env);
	else if (strcmp(argv[1], "echo") == 0)
		ft_echo(argv+2);
	else if (strcmp(argv[1], "env") == 0)
		ft_env(env);		
	else if (strcmp(argv[1], "export") == 0)
		ft_export(argv+2, env);
}
