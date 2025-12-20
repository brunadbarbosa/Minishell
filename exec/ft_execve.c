/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:51:11 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/20 18:11:07 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_path(char *cmd, char **envp);
static void	ft_free(char **str);
static char	*ft_str2join(char *path, char *str1, char *str2);

void	print_error(char *cmd, char *str, int stdfd)
{
	ft_putstr_fd(cmd, stdfd);
	ft_putstr_fd(str, stdfd);
}

/// @brief calls execve
/// @param cmd the arguments contained in t_cmd->args
/// @param envp the environment parsed into char**
void	ft_execve(char **cmd, char **envp, t_shell *shell)
{
	char	*path;

	if (!cmd || !*cmd || !envp || !*envp)
		return ;
	if (!cmd[0][0] || cmd[0][0] == '/'
		|| (cmd [0][0] == '.' && cmd[0][1] == '/'))
	{
		if (access(cmd[0], F_OK | X_OK))
			return (print_error(cmd[0], ": command not found\n", 2));
		path = cmd[0];
	}
	else
		path = ft_path(cmd[0], envp);
	if (!path)
	{
		print_error(cmd[0], ": command not found\n", 2);
		ft_free_args(envp);
		ft_clean_shell(shell, NULL);
		exit(127);
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
	if (envp[i] == NULL || !envp[i][5])
		return (ft_putstr_fd("PATH not found\n", 2), NULL);
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
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
