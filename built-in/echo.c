/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:49:42 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:04:15 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verif_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_len_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	ft_echo(char **args)
{
	int	i;
	int	var;

	if (args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (args[1] && (ft_strncmp(args[1], "-n", 2) == 0)
		&& verif_n(args[1] + 2) == 1)
		i = 2;
	else
		i = 1;
	var = i;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] && args[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (ft_strncmp(args[1], "-n", 2) != 0 || var == 1)
		printf("\n");
}

int	ft_print_env(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->var, env->value);
		else
			printf("%s\n", env->var);
		env = env->next;
	}
	return (1);
}

