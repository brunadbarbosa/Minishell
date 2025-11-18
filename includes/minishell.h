/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:36:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/18 18:45:58 by adpinhei         ###   ########.fr       */
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
# include "structs.h"

/*****************************************************************************\
*                                Parsing Functions                            *
\*****************************************************************************/

void	loop(t_shell *shell);
void	ft_init_shell(t_shell *shell, char **envp);
void	ft_exit(t_shell *shell, char *input);
void	ft_parser(t_shell *shell);
void	ft_lexer(t_shell *shell, char *input);
void	ft_settokentype(t_token *token);
void	ft_expand(t_token **lst, t_env *env);

t_token	*ft_new_token(char *input, ssize_t size);
t_token	*ft_init_token(ssize_t size);

ssize_t	ft_tokensize(char *input);
ssize_t	ft_operatorsize(char *input);

bool	ft_isspace(const char c);
bool	is_operator(const char *str);
bool	is_quote(const char str);
bool	is_delimiter(const char *str);

e_redir_type	redirtype(e_token_type type);

/*****************************************************************************\
*                                Cleaning Functions                           *
\*****************************************************************************/

void	ft_clean_shell(t_shell *shell, char *msg);
void	ft_clean_cmd_lst(t_cmd **lst, char *msg);
void	ft_clean_env(t_env **env, char *msg);
void	ft_clean_tokens(t_token **lst, char *msg);
void	ft_clean_redirs(t_redir **redirs);
void	ft_free_args(char **args);

#endif