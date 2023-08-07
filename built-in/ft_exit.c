#include "../includes/minishell.h"

int		word_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && (str[i] != '+' && str[i] != '-'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_one_sign(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '+' || str[i] == '-'))
			flag = 1;
		else if (flag == 1 && (str[i] == '+' || str[i] == '-'))
			return (-1);
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
			return (exit_code = 1, 1);
		}
		if (word_numeric(argv[i]) == 0 || ft_check_one_sign(argv[i]) == -1)
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
		return ;
	else if (argv[1] == NULL)
		ft_free_all_exit(5, 0, env, argv);
	else if (error == 2)
		ft_free_all_exit(5, ft_atoi(argv[1]), env, argv);
	else if (argv[1] && error == 0)
		ft_free_all_exit(5, ft_atoi(argv[1]), env, argv);
}
