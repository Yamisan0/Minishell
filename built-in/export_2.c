/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:52:40 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:05:56 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_valid_variable(char *str)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '-')
			check = 1;
		i++;
	}
	if ((str[0] && str[0] == '=') || check == 1 || (str[0] && ft_isdigit(str[0])))
		return (ft_printf(
				"minishell: export: `%s': not a valid identifier\n", str), exit_code = 1, 0);
	return (1);
}

int	export_parsing(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (check_valid_variable(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_norm_export(t_env *tmp, char **argv, int i, t_env *head)
{
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = ft_strdup(return_equal(argv[i]));
	}
	else
	{
		tmp = create_node(argv[i]);
		cpy_tab(argv[i], tmp);
		head = add_to_list(head, tmp);
	}
}

void	ft_export(t_env **env, char **argv)
{
	t_env	*tmp;
	t_env	*head;
	int		i;

	head = *env;
	tmp = *env;
	i = 1;
	while (argv[i])
	{
		if (check_valid_variable(argv[i]) == 0)
		{
			i++;
			continue ;
		}
		tmp = ft_check_exist(*env, argv[i]);
		ft_norm_export(tmp, argv, i, head);
		i++;
	}
	*env = head;
}
