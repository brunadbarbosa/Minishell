/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:36:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/10 20:06:32 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "parser.h"


typedef	enum e_redir_type
{
	REDIR_IN, // <
	REDIR_OUT, // >
	REDIR_APPEND, // >>
	REDIR_HERE // <<
}	e_redir_type;

/// @brief these structs will form our environment.
typedef	struct s_env
{
	char			*name; //variable name.
	char			**value; //variables expansion.
	struct s_env	*next;
}	t_env;

/// @brief redirection details. t_cmd will have a pointer to this.
typedef	struct s_redir
{
	e_redir_type	type; //macros for the type of redirection (e.g. '<', '>>')
	char			*file; //the name of the redirection file. If HEREDOC, this means EOF.
	int				fd; //holds the redirection file's fd. Will be initialized to -1
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

typedef	struct s_shell
{
	t_env	*env; //envp list
	t_token	*tokens; //token list
	t_cmd	*cmds; //command list
	int		exit_status; //last command exit status for $?
}	t_shell;

/*****************************************************************************\
*                                Main Functions                               *
\*****************************************************************************/

void	loop(void);
void	ft_init_shell(t_shell *shell, char **envp);

/*****************************************************************************\
*                                Cleaning Functions                           *
\*****************************************************************************/

void	ft_clean_shell(t_shell *shell, char *msg);
void	ft_clean_env(t_env *env, char *msg);
void	ft_free_args(char **args);

#endif