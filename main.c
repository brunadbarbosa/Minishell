/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:19:51 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/15 18:38:22 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	
	env = init_env_list(envp);
	(void)argc;
	if (ft_strncmp(argv[1], "pwd", 3) == 0)
		ft_pwd(env);
	else if (ft_strncmp(argv[1], "echo", 4) == 0)
		ft_echo(argv+2);
	else if (ft_strncmp(argv[1], "env", 3) == 0)
		ft_env(env);		
	else if (ft_strncmp(argv[1], "export", 6) == 0)
		ft_export(argv+2, env);
	else if (ft_strncmp(argv[1], "unset", 5) == 0)
		ft_unset();
}
