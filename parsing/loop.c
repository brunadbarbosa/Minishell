/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:36:36 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/18 18:46:59 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	ft_printlst(t_shell *shell)
// {
// 	int	i = 1;
// 	if (!shell)
// 		return ;
// 	t_token *current = shell->tokens;
// 	while (current)
// 	{
// 		ft_printf("TOKEN #%i\n [value: %s]\n [type: %i]\n***\n",i, current->value, current->type);
// 		i++;
// 		current = current->next;
// 	}
// }

// static void	print_env(t_shell *shell)
// {
// 	if (!shell)
// 	{
// 		ft_printf("No shell\n");
// 		return ;
// 	}
// 	t_env	*env = shell->env;
// 	while(env->next)
// 	{
// 		ft_printf("[var name] %s\n", env->name);
// 		ft_printf("\t[value] %s\n", env->value);
// 		env = env->next;
// 	}
// 	ft_printf("[var name] %s\n", env->name);
// 	ft_printf("\t[value] %s\n", env->value);
// }

static void	ft_printcmd(t_shell *shell)
{
	if (!shell)
		return ;
	t_cmd	*current = shell->cmds;
	while (current)
	{
		ft_printf("[cmd name] %s\n", current->cmd);
		if (current->args)
		{
			int	j = 0;
			while (current->args[j])
			{
				ft_printf("\t\t[args] %s\n", current->args[j]);
				j++;
			}
		}
		if (current->redirs)
		{
			while (current->redirs)
			{
				ft_printf("\t\t[redir type] %i\n", current->redirs->type);
				ft_printf("\t\t[redir file] %s\n", current->redirs->file);
				current->redirs = current->redirs->next;
			}
		}
		if (current->next)
			ft_printf("\t\t[pipes to] %s\n", current->next->cmd);
		ft_printf("\n\n");
		current = current->next;
	}
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
//		ft_syntax(shell); verify valid syntax
//		ft_printlst(shell);//remove this tester
		ft_parser(shell);//make the cmd list
		ft_printcmd(shell);//remove this tester
		free(input);
		ft_clean_tokens(&shell->tokens, NULL);
		ft_clean_cmd_lst(&shell->cmds, NULL);
	}
}

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
