/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:58:51 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/12 16:47:29 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_numeric(char *str)
{
	int	i;
	int	var;

	var = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			var = 1;
		else if (ft_isdigit(str[i]) == 0 && (str[i] != '+' && str[i] != '-'))
			return (0);
		if (var == 1 && ft_isdigit(str[i]) == 0)
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
	if ((str[0] == '+' || str[0] == '-') && str[1] == '\0')
		return (-1);
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

int	ft_exit_parsing(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (i >= 2)
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (g_ecode = 1, 1);
		}
		if (ft_strcmp("-9223372036854775808", argv[i]) == 0)
			return (0);
		if (word_numeric(argv[i]) == 0 || ft_check_one_sign(argv[i]) == -1
			|| (ft_atoi(argv[i]) == -1625893402))
		{
			write(2, "minishell: exit: ", 17);
			ft_putstr_fd(argv[i], 2);
			write(2, ": numeric argument required\n", 29);
			g_ecode = 2;
			return (2);
		}
		i++;
	}
	return (0);
}

int	nbr_exit_negatif(char *str)
{
	long long	nbr;

	if (ft_strcmp("-9223372036854775808", str) == 0)
		return (0);
	nbr = ft_atoi(str);
	nbr = nbr * (-1);
	nbr = nbr % 256;
	nbr = 256 - nbr;
	return (nbr);
}

void	ft_exit(char **argv, t_env *env, int old_gecode)
{
	int		error;

	printf("exit\n");
	error = ft_exit_parsing(argv);
	if (error == 1)
		return ;
	else if (argv[1] == NULL)
		ft_free_all_exit(5, old_gecode, env, argv);
	else if (error == 2)
		ft_free_all_exit(5, g_ecode, env, argv);
	else if (argv[1] && error == 0)
	{
		if (argv[1][0] != '-')
			ft_free_all_exit(5, ft_atoi(argv[1]), env, argv);
		else
		{
			ft_free_all_exit(5, nbr_exit_negatif(argv[1]), env, argv);
		}
	}
}
