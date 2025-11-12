/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/12 19:39:42 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_printlst(t_token **lst)
{
	int	i = 1;
	if (!lst || !*lst)
		return ;
	t_token *current = *lst;
	while (current)
	{
		ft_printf("TOKEN #%i\n [value: %s]\n [type: %i]\n***\n",i, current->value, current->type);
		i++;
		current = current->next;
	}
}

static void	print_env(t_shell *shell)
{
	if (!shell)
	{
		ft_printf("No shell\n");
		return ;
	}
	t_env	*env = shell->env;
	while(env->next)
	{
		ft_printf("[var name] %s\n", env->name);
		ft_printf("\t[value] %s\n", env->value);
		env = env->next;
	}
	ft_printf("[var name] %s\n", env->name);
	ft_printf("\t[value] %s\n", env->value);
}
void	loop(t_shell *shell)
{
	char	*input;

	if(!shell)
		return ;
	while (true)
	{
		input = readline("minishell> ");
		ft_exit(shell, input);
		add_history(input);
		ft_lexer(shell, input);//puts tolkens
		ft_printlst(&shell->tokens);//remove this tester
		ft_parser(shell);//make the cmd list
//		ft_printcmd(shell);//remove this tester
		free(input);
		ft_clean_shell(shell, NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_init_shell(&shell, envp);
	print_env(&shell);
	loop(&shell);
	ft_clean_shell(&shell, NULL);
	return (shell.exit_status);
}
