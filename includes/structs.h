/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:29:06 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/18 15:41:45 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER
# define PARSER

# include "minishell.h"

/// @brief macros for token identification
typedef	enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_RED_IN,
	TOKEN_RED_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	e_token_type;

typedef	enum e_redir_type
{
	REDIR_IN = 2, // <
	REDIR_OUT, // >
	REDIR_APPEND, // >>
	REDIR_HERE // <<
}	e_redir_type;

/// @brief structs for tolkens
typedef	struct s_token
{
	e_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/// @brief these structs will form our environment.
typedef	struct s_env
{
	char			*name; //variable's name.
	char			*value; //variable's expansion.
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

#endif