#include "../includes/minishell.h"

int		word_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_exit_parsing(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (i >= 2)
		{
			write(2, "minishell: exit: too many arguments\n",37);
			return (1);
		}
		if (word_numeric(argv[i]) == 0)
		{
			write(2, "minishell: exit: ", 17);
			ft_putstr_fd(argv[i], 2);
			write(2, ": numeric argument required\n", 29);
			return (2);
		}
		i++;
	}
	return (0);
}

void    ft_exit(char **argv, t_env *env)
{
	int		error;
	
	printf("exit\n");
	error = ft_exit_parsing(argv);
	if (error == 1)
	{
		ft_free_split(argv);
		return ;
	}
	if (argv[1] == NULL)
	{
		ft_free_split(argv);
		ft_free_all_exit(5, 0, env);
	}
	if (error == 2)
	{
		ft_free_split(argv);
		ft_free_all_exit(5, 2, env);
	}
	if (argv[1] && error == 0)
	{
		ft_free_split(argv);
		ft_free_all_exit(5, ft_atoi(argv[1]), env);
	}
}
