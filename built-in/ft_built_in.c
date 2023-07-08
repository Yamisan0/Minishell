#include "../includes/minishell.h"

int	ft_check_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(argv[0], "exit") == 0)
		return (1);
	return (-1);
}

int	ft_built_in(char **argv, t_env *env)
{
	if (!argv)
		return (-1);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv), 1);
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_print_env(env), 1);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv + 1), 1);
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(), 1);
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(env, argv[1]), 1);
	return (-1);
}