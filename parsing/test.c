/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:10:51 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/18 21:11:30 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printlst(t_shell *shell)
{
	int	i = 1;
	if (!shell)
		return ;
	t_token *current = shell->tokens;
	while (current)
	{
		ft_printf("TOKEN #%i\n [value: %s]\n [type: %i]\n***\n",i, current->value, current->type);
		i++;
		current = current->next;
	}
}

void	print_env(t_shell *shell)
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

void	ft_printcmd(t_shell *shell)
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
			t_redir	*tmp = current->redirs;
			while (tmp)
			{
				ft_printf("\t\t[redir type] %i\n", tmp->type);
				ft_printf("\t\t[redir file] %s\n", tmp->file);
				tmp = tmp->next;;
			}
		}
		if (current->next)
			ft_printf("\t\t[pipes to] %s\n", current->next->cmd);
		ft_printf("\n\n");
		current = current->next;
	}
}
