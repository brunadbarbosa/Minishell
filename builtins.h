/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:19:33 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/15 18:36:11 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


typedef	enum e_redir_type
{
	REDIR_IN, // <
	REDIR_OUT, // >
	REDIR_APPEND // >>
}	e_redir_type;

/// @brief these structs will form our environment.
typedef	struct s_env
{
	char			*name; //variable name.
	char			*value; //variables expansion.
	struct s_env	*next;
}	t_env;

/// @brief redirection details. t_cmd will have a pointer to this.
typedef	struct s_redir
{
	e_redir_type	type; //macros for the type of redirection (e.g. '<', '>>')
	char			*file; //the name of the redirection file
	struct s_redir	*next; //list of redirections (e.g. "< infile cat > outfile", which has both REDIR_IN and REDIR_OUT)
}	t_redir;

/// @brief main struct to be passed for execution
typedef	struct s_cmd
{
	char			*cmd; //command name
	char			**args; //arguments to the command
	t_redir			*redirs; //linked list of redirections, NULL if none
	struct s_cmd	*next; //if there is a pipe, the address of the next cmd will be here. If no, this will be NULL
}	t_cmd;

// echo
void	ft_echo(char **args);
// env
void	ft_env(t_env *env);
t_env	*init_env_list(char **envp);
t_env	*create_env_node(const char *env_str);
//export
int	check_args(char **args);
void	ft_export(char **args, t_env *env);
//pwd
void	ft_pwd(t_env *env);

#endif