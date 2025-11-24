/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:20:08 by adpinhei          #+#    #+#             */
/*   Updated: 2025/11/24 19:49:00 by adpinhei         ###   ########.fr       */
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

/// @brief turns t_env *env into char **envstr
/// @return the char** that holds the environment
static char	**ft_envstr(t_env *lst)
{
	char	**envstr;
	t_env	*env;
	int		i;

	if (!lst)
		return (NULL);
	i = 0;
	env = lst;
	while (env)
	{
		i++;
		env = env->next;
	}
	envstr = malloc(sizeof(char *) * (i + 1));
	if (!envstr)
		return (NULL);
	envstr[i] = NULL;
	i = 0;
	env = lst;
	while (envstr[i])
	{
		envstr[i] = get_env_name(env);
		if (!envstr[i])
		{
			//clear envstr and return NULL
		}
		i++;
		env = env->next;
	}
	return (envstr);
}

static char	*get_env_name(t_env *env)
{
	char	*res;

	if (!env)
		return (NULL);
	res = /*strdup of env->name*/
	/*concatenate '='
	  concatenate env->value*/
}