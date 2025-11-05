/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:36:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/05 11:29:12 by adpinhei         ###   ########.fr       */
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

/// @brief these structs will form our environment.
typedef	struct s_env
{
	char			*name; //variable name.
	char			**value; //variables expansion.
	struct s_env	*next;
}	t_env;

/// @brief struct to hold the file's information.
typedef	struct s_file
{
	int		is_heredoc; //0 if it is not, 1 if it is.
	int		fd_in;
	int		fd_out;
	char	*name;
}	t_file;

/// @brief struct to hold the user's input. Will be parsed into t_shell.
typedef	struct s_input
{
	char	*input; //holds input from the user.
	int		in_quotes; //tells if we are in quotes.
}	t_input;

// /// @brief main struct to be passed to execution. 
// typedef	struct s_shell
// {
// 	int		type; //macros defined as program, built-in, or operator.
// 	char	*cmd; //the command to be executed.
// 	char	**args; //args to cmd. NULL if nothing to be passed as argument.
// 	int		exit_status; //holds the return from processes.
// 	t_env	*env; //header to the environment.
// 	t_file	*file; //struct to any needed infile or outfile.
// 	t_shell	*left;
// 	t_shell	*right;
// 	t_shell	*prev;
// }	t_shell;



#endif