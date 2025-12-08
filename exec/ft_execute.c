/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:20:08 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/08 15:31:33 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_envstr(t_env *lst);
static char	*get_envp(t_env *env);
static int	ft_envsize(t_env *lst);
static int	is_builtin(t_cmd *cmd);
void		execute_builtin(t_shell *shell);

/// @brief passes the command to execve
/// @param cmd the command to be executed
/// @param env environment to be turned into char** and then passed
/// @param shell the main struct
void	ft_execute(t_cmd *cmd, t_env *env, t_shell *shell)
{
	char	**envp;

	if (!cmd || !shell)
		return ;
	if (is_builtin(cmd))
	{
//		execute_builtin(shell);
		printf("builtin\n");
		return ;
	}
	else
	{
		envp = ft_envstr(env);
		if (!envp)
			return ;
		ft_execve(cmd->args, envp);
		ft_free_args(envp);
	}
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
	envstr = malloc(sizeof(char *) * (ft_envsize(lst) + 1));
	if (!envstr)
		return (NULL);
	i = 0;
	env = lst;
	while (env)
	{
		envstr[i] = get_envp(env);
		if (!envstr[i])
		{
			ft_free_args(envstr);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envstr[i] = NULL;
	return (envstr);
}

/// @brief concatenates env->name + '=' + env->value
/// @param env the t_env node
/// @return the string with a variable in envp format
static char	*get_envp(t_env *env)
{
	char	*res;
	char	*tmp;

	if (!env)
		return (NULL);
	res = ft_strdup(env->name);
	tmp = ft_strjoin(res, "=");
	free(res);
	res = tmp;
	tmp = NULL;
	tmp = ft_strjoin(res, env->value);
	free(res);
	res = tmp;
	tmp = NULL;
	return (res);
}

static int	ft_envsize(t_env *lst)
{
	int	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst != NULL)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

static int	is_builtin(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("echo", cmd->cmd, 5))
		return (1);
	if (!ft_strncmp("cd", cmd->cmd, 3))
		return (1);
	if (!ft_strncmp("pwd", cmd->cmd, 4))
		return (1);
	if (!ft_strncmp("export", cmd->cmd, 7))
		return (1);
	if (!ft_strncmp("unset", cmd->cmd, 6))
		return (1);
	if (!ft_strncmp("env", cmd->cmd, 4))
		return (1);
	if (!ft_strncmp("exit", cmd->cmd, 5))
		return (1);
	return (0);
}
