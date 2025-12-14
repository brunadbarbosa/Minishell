/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:33:55 by brmaria-          #+#    #+#             */
/*   Updated: 2025/12/14 19:23:30 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		exit_status;

	(void)argc;
	(void)argv;
	shell = NULL;
	shell = ft_init_shell(shell, envp);
	g_exit_status = shell->exit_status;
	init_interactive_mode();
	loop(shell);
	exit_status = shell->exit_status;
	ft_clean_shell(shell, NULL);
	return (exit_status);
}
