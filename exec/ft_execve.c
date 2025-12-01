/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:51:11 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/01 16:21:29 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_path(char *cmd, char **envp);
static void	ft_free(char **str);
static char	*ft_str2join(char *path, char *str1, char *str2);

/// @brief calls execve
/// @param cmd the arguments contained in t_cmd->args
/// @param envp the environment parsed into char**
void	ft_execve(char **cmd, char **envp)
{
	char	*path;

	if (!cmd || !*cmd || !envp || !*envp)
		return ;
	path = ft_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("Failed at ft_execve\n", 2);
		return ;
	}
	execve(path, cmd, envp);
	free(path);
	path = NULL;
}

/// @brief finds the path to the command
/// @return a str containing the actual path for execve to execute or NULL
static char	*ft_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (ft_putstr_fd("PATH not found\n", 2), NULL);
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i++])
	{
		path_cmd = ft_str2join(path[i], "/", cmd);
		if (!path_cmd)
			return (ft_free(path), NULL);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (ft_free(path), path_cmd);
		free(path_cmd);
	}
	ft_free(path);
	return (NULL);
}

/// @brief helper function to free a char**
/// @param str 
static void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

/// @brief calls ft_strjoin twice, concatenating three strings
/// @return the triple concatenated str or NULL
static char	*ft_str2join(char *path, char *str1, char *str2)
{
	char	*temp;
	char	*dest;

	if (!path || !str1 || !str2)
		return (NULL);
	temp = ft_strjoin(path, str1);
	if (!temp)
		return (NULL);
	dest = ft_strjoin(temp, str2);
	if (!dest)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	free(temp);
	temp = NULL;
	return (dest);
}
