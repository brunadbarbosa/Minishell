#include "../includes/minishell.h"

static int	ft_close_token_lst(t_token **token_lst);
static void	ft_add_token(t_token **lst, t_token *new);

/// @brief tokenizes the input
/// @param input line from the user
void	ft_lexer(t_shell *shell, char *input)
{
	t_token	*token_node;
	ssize_t	size;
	int		i;

	if (!input)
		return ;
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		size = ft_tokensize(&input[i]);
		if (size == -1)
			return (ft_putstr_fd("Unclosed quotes\n", 2));
		token_node = ft_new_token(&input[i], size);
		if (!token_node)
			return (ft_clean_shell(shell, "Failed to allocate token\n"));
		ft_add_token(&shell->tokens, token_node);
		i += size;
	}
	if (ft_close_token_lst(&shell->tokens))
		ft_clean_shell(shell, "Failed to close token_lst\n");
	ft_expand(&shell->tokens, shell->env);
}

/// @brief closes the token list with eof
static int	ft_close_token_lst(t_token **token_lst)
{
	t_token	*closing_token;

	closing_token = ft_new_token("eof", 3);
	if (!closing_token)
		return (1);
	ft_add_token(token_lst, closing_token);
	return (0);
}

/// @brief adds newly generated token nodes to the token list
/// @param lst the head of the token list
/// @param new the new token to be added to the list
static void	ft_add_token(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}
