/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:19:33 by brmaria-          #+#    #+#             */
/*   Updated: 2025/11/24 13:33:28 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


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
	int		fd_in;
	int		fd_out;
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
	int		exit_status;
}	t_shell;

// echo
void	ft_echo(char **args);
// env
void	ft_env(t_env *env);
t_env	*init_env_list(char **envp);
t_env	*create_env_node(const char *env_str);
//export
int	check_args(char *args);
void	ft_export(char **args, t_env *env);
//pwd
char	*get_current_path(void);
void	ft_pwd(t_env *env);
//unset
void	ft_unset(char **args, t_env **env);
//cd
void	ft_cd(char **args, t_shell **shell);

#endif