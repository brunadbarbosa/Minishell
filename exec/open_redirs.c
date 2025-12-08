/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:20 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/08 16:14:28 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_redir(t_redir *red, t_shell *shell);
static char	*gen_filename(void);
static void	ft_add_here(char ***heredoc, char *file);
static void	ft_add_here_util(char ***heredoc, char *file);

/// @brief iterates through the command list to find redirections
/// @param cmdlst the list of commands
/// @param shell the master struct
void	ft_openredirs(t_cmd *cmdlst, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*red;

	if (!cmdlst)
		return ;
	cmd = cmdlst;
	while (cmd)
	{
		red = cmd->redirs;
		if (red)
		{
			while (red)
			{
				get_redir(red, shell);
				red = red->next;
			}
		}
		cmd = cmd->next;
	}
}

/// @brief gets the file descriptors for the redirections
/// @param red the t_redir struct with redirection info
static void	get_redir(t_redir *red, t_shell *shell)
{
	char	*filename;

	if (red->type == REDIR_APPEND)
		red->fd = open(red->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (red->type == REDIR_IN)
		red->fd = open(red->file, O_RDONLY, 0644);
	else if (red->type == REDIR_OUT)
		red->fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red->type == REDIR_HERE)
	{
		filename = gen_filename();
		red->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (red->fd < 0)
			return (free(filename));
		read_into_here(red->fd, red->file);
		close(red->fd);
		red->fd = open(filename, O_RDONLY);
		if (red->fd < 0)
			return (free(filename));
		ft_add_here(&shell->heredoc, filename);
		free(filename);
	}
	return ;
}

/// @brief generates a random filename based on /dev/urandom
/// @return the filename
static char	*gen_filename(void)
{
	char	*filename;
	char	buffer[20];
	ssize_t	i;
	int		j;

	j = open("/dev/urandom", O_RDONLY);
	if (j < 0)
		return (NULL);
	i = read(j, &buffer, 20);
	close (j);
	if (i < 0)
		return (NULL);
	filename = malloc(sizeof(char) * 22);
	if (!filename)
		return (NULL);
	filename[0] = '.';
	j = 0;
	while (++j < 22)
	{
		if (buffer[j] < 32 || buffer[j] > 126)
			filename[j] = '0';
		else
			filename[j] = buffer[j];
	}
	return (filename[j] = '\0', filename);
}

/// @brief allocates the filename's string into shell->heredoc
/// @param heredoc the head to shell->heredoc
/// @param file the name of file to be used to store heredoc
static void	ft_add_here(char ***heredoc, char *file)
{
	if (!file)
		return ;
	if (!*heredoc)
	{
		*heredoc = malloc(sizeof(char *) * 2);
		if (!*heredoc)
			return ;
		(*heredoc)[0] = ft_strdup(file);
		if (!*heredoc)
			return ;
		(*heredoc)[1] = NULL;
	}
	else
		ft_add_here_util(heredoc, file);
}

/// @brief adds a new string at the end of shell->heredoc
static void	ft_add_here_util(char ***heredoc, char *file)
{
	int		i;
	char	**temp;

	i = 0;
	while ((*heredoc)[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return ;
	i = 0;
	while ((*heredoc)[i])
	{
		temp[i] = (*heredoc)[i];
		i++;
	}
	temp[i] = ft_strdup(file);
	if (!temp[i])
	{
		ft_free_args(temp);
		return ;
	}
	temp[++i] = NULL;
	free(*heredoc);
	*heredoc = temp;
	free(temp);
}
