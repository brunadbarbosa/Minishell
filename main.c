/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:01:19 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/02 18:53:12 by adpinhei         ###   ########.fr       */
/*   Updated: 2025/12/01 17:42:22 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_init_shell(&shell, envp);
//	print_env(&shell);
	loop(&shell);
	ft_clean_shell(&shell, NULL);
	return (shell.exit_status);
}
