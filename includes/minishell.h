/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:54:41 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/30 18:11:56 by brmaria-         ###   ########.fr       */
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
void			my_exit(t_shell *shell, char *input);
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
/*                                  Builtin Functions                        */
/*****************************************************************************/

void	change_env(char *old_pwd, char *new_pwd, t_shell *shell);
char	*get_bigger_buffer(char *prev, int prev_len, int new_prev_len);
char	*copy_from_env(char **args, t_shell *shell);
char	*get_current_path(void);
void	ft_cd(t_shell *shell);

void	ft_echo(char **args, t_shell *shell);

void	ft_env(t_env *env);

int		safe_atoll(const char *str, long long *out);
void	ft_exit(char **args, char *cmd, t_shell *shell);

t_env	*create_env_node(const char *env_str);
int		check_args(char *args);
t_env	*get_value(t_env *env, char *name);
void 	set_value(char *str, t_env **env);
void	ft_export(char **args, t_shell *shell);

void	check_is_builtin(t_shell *shell);

char 	*getpwd(t_env *env);
void	ft_pwd(t_env *env);

void	remove_env(t_env **env, char *name);
void	ft_unset(char **args, t_env *env, t_shell *shell);

/*****************************************************************************/
/*                                  Exec Functions                           */
/*****************************************************************************/

void			ft_exec(t_shell *shell);

/******************************************************************************/
/*                                Cleaning Functions                          */
/******************************************************************************/

void			ft_clean_shell(t_shell *shell, char *msg);
void			ft_clean_cmd_lst(t_cmd **lst, char *msg);
void			ft_clean_env(t_env **env, char *msg);
void			ft_clean_tokens(t_token **lst, char *msg);
void			ft_clean_redirs(t_redir **redirs);
void			ft_free_args(char **args);

#endif