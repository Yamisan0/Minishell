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

int check_pipe_prev(t_lexer *args)
{
	 t_lexer *tmp;

	tmp = args;
	while (tmp)
	{
		if (args->prev && args->token == PIPE)
			return(1);
		tmp = tmp->prev;
	}
	return (0);
}

int	ft_norm_built_in(char **argv)
{
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(), 1);
	if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	return (0);
}

int	ft_built_in(char **argv, t_env *env, t_lexer *args)
{
	if (!argv)
		return (-1);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv), 1);
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_print_env(env), 1);
	if (ft_strcmp(argv[0], "cd") == 0 && check_pipe_prev(args) == 1)
		return (ft_cd(argv + 1, NULL), 1);
	if (ft_norm_built_in(argv) == 1)
		return (1);
	if (ft_strcmp(argv[0], "export") == 0)
	{
		if (!argv[1])
			ft_export_sans_arg(env);
		if (args->prev)
			return (export_parsing(argv), 1);
		return (1);
	}
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		if (args->prev)
			return (ft_exit_parsing(argv), 1);
		return (1);
	}
	return (-1);
}
