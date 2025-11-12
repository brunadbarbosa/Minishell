#include "../includes/minishell.h"

/// @brief initialize the super struct t_shell
/// @param shell the super struct
/// @param envp the pointer to the environment variables
void	ft_init_shell(t_shell *shell, char **envp)
{
	if (!shell)
		return ;
	if (!envp)
	{
		ft_putstr_fd("No environment\n", 2);
		return ;
	}
	shell->cmds = NULL;
	shell->tokens = NULL;
	shell->exit_status = 0;
	shell->env = ft_env(&shell, envp);
}

/// @brief initializes the local environment
/// @param envp the pointer to the environment variables
/// @return the list to be used as local environment
t_env	*ft_env(t_shell *shell, char **envp)
{
	t_env	*env;
	int		i;
	int		j;

	if (!envp)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		ft_strlcpy(env->name, envp[i], j);
		env->value = ft_strdup(&envp[i + j + 1]);
		i++;
	}
	return (env);
}
