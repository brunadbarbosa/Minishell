#include "../includes/minishell.h"

void	ft_exit(t_shell *shell, char *input)
{
	size_t	len;

	len = ft_strlen(input);
	if (len == 0)
		return ;
	if (!ft_strncmp(input, "exit", len))
	{
		ft_clean_shell(shell, NULL);
		exit(EXIT_SUCCESS);
	}
}
