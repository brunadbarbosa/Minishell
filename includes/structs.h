/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:29:06 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/02 20:40:27 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_RED_IN,
	TOKEN_RED_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE
}	t_redir_type;

/// @brief to be used in execution phase to deal with fd redirections
typedef struct s_pipe
{
	pid_t	*pids;
	int		pid_count;
	int		pipefd[2];
	int		prev_read_fd;
	char	**heredocs;
}	t_pipe;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/// @brief these structs will form our environment.
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/// @brief redirection details. t_cmd will have a pointer to this.
typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}	t_redir;

/// @brief main struct to be passed for execution
typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	int		std_in;
	int		std_out;
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmds;
	char	**heredoc;
	int		exit_status;
}	t_shell;

#endif