/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:29:06 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/11 18:38:08 by adpinhei         ###   ########.fr       */
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

/// @brief structs for tolkens
typedef	struct s_token
{
	e_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;


/*****************************************************************************\
*                            Input Parsing Functions                          *
\*****************************************************************************/

bool	ft_isspace(const char c);
bool	is_operator(const char *str);
bool	is_quote(const char str);
bool	is_delimiter(const char *str);

/*****************************************************************************\
*                               Tokenizer Functions                           *
\*****************************************************************************/

void	ft_lexer(t_shell *shell, char *input);
void	ft_add_token(t_token **lst, t_token *new);
void	ft_settokentype(t_token *token);

t_token	*ft_new_token(char *input, ssize_t size);
t_token	*ft_init_token(ssize_t token_size);

ssize_t	ft_tokensize(char *input);
ssize_t	ft_operatorsize(char *input);

/*****************************************************************************\
*                           Error & Cleaning Functions                        *
\*****************************************************************************/

void	ft_clean_tokens(t_token **lst, char *msg);
void	ft_clean_cmd_lst(t_cmd *lst, char *msg);

#endif