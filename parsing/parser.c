#include "../includes/minishell.h"

void	ft_parser(t_shell *shell)
{
	if (!shell)
		return ;
	ft_cmd_lst_init(&shell);
	ft_cmd_lst(&shell);
}

void	ft_cmd_lst_init(t_shell *shell)
{
	if (!shell)
		return ;
	shell->cmds = malloc(sizeof(t_cmd));
	if (!shell->cmds)
		ft_clean_shell(&shell, "Failed allocating t_cmd\n");
	shell->cmds->cmd = NULL;
	shell->cmds->args = NULL;
	shell->cmds->next = NULL;
	shell->cmds->redirs = NULL;
}

void	ft_cmd_lst(t_shell *shell)
{
	t_token	*token;

	token = shell->tokens;
	while (token->type != TOKEN_EOF)
	{
		ft_addcmd(shell->cmds, token); //identify the token type, build the shell->cmd
		token = token->next;
	}
	token = NULL;
	//identify token type
	//if redirection, allocate cmd_lst->redirs
	//if (!eof && !redir && !pipe) make cmd name and cmd args
	//if pipe, cmd->next
	//if heredoc, find eoh (end of heredoc)
}

void	ft_addcmd(t_cmd **cmds, t_token *token)
{
	t_cmd	*current;

	if (!token)
		return ;
	current = *cmds;
	if (!current)
		current = ft_new_cmd(token);
	else
	{
		while (current->next)
			current = current->next;
		//if pipe, connect current to current->next
		current->next = ft_new_cmd(token);
	}
}

t_cmd	*ft_new_cmd(t_token *token)
{
	//identify token type
	//if redir, ft_redir()
	//allocate for the new cmd
	//cmd.name
	//cmd.args
	//if pipe...?
}
