#include "../includes/minishell.h"

int	ft_check_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(argv[0], "env"))
		return (1);
	return (-1);
}

int	ft_built_in(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv), 1);
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_print_env(global_env));
	return (-1);
}