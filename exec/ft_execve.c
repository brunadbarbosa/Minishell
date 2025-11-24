/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:20:08 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/24 18:44:40 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief passes the command to execve
/// @param cmd the command to be executed
/// @param env environment to be turned into char** and then passed
/// @param shell the main struct
void	ft_execve(t_cmd *cmd, t_env *env, t_shell *shell)
{
	if (!cmd || !shell)
		return ;
	/*turn env into a char**
	  find the path
	  pass it to execve
	  clean if execve returns*/
}
