/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:54:41 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/24 19:36:56 by adpinhei         ###   ########.fr       */
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
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "structs.h"

/*****************************************************************************/
/*                                Parsing Functions                          */
/*****************************************************************************/

void			loop(t_shell *shell);
void			ft_init_shell(t_shell *shell, char **envp);
void			ft_exit(t_shell *shell, char *input);
void			ft_parser(t_shell *shell);
void			ft_lexer(t_shell *shell, char *input);
void			ft_settokentype(t_token *token);
void			ft_expand(t_token **lst, t_env *env);
void			ft_syntax(t_shell *shell);
void			ft_initredir(t_redir *redir, t_token *tk);

t_token			*ft_new_token(char *input, ssize_t size);
t_token			*ft_init_token(ssize_t size);

ssize_t			ft_tokensize(char *input);
ssize_t			ft_operatorsize(char *input);

bool			ft_isspace(const char c);
bool			is_operator(const char *str);
bool			is_quote(const char str);
bool			is_delimiter(const char *str);

int				ft_openquotes(int i, int quotes);
int				ft_buildnextcmd(t_cmd **current, t_cmd *head);
int				ft_initcmdlist(t_token **tk, t_token *tks, t_cmd **h, t_cmd **c);

t_redir_type	redirtype(t_token_type type);

/*testing functions*/

void			ft_printlst(t_shell *shell);
void			print_env(t_shell *shell);
void			ft_printcmd(t_shell *shell);

/*****************************************************************************/
/*                                  Exec Functions                           */
/*****************************************************************************/

void			ft_exec(t_shell *shell);
void			ft_openredirs(t_cmd *cmdlst);
int				ft_pipe(t_cmd *cmdlst);
void			ft_execve(t_cmd *cmd, t_env *env, t_shell *shell);

/******************************************************************************/
/*                                Cleaning Functions                          */
/******************************************************************************/

void			ft_clean_shell(t_shell *shell, char *msg);
void			ft_clean_cmd_lst(t_cmd **lst, char *msg);
void			ft_clean_env(t_env **env, char *msg);
void			ft_clean_tokens(t_token **lst, char *msg);
void			ft_clean_redirs(t_redir **redirs);
void			ft_free_args(char **args);
void			ft_closepipe(int fd1, int fd2, char *str);

#endif