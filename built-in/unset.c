/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:01:09 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/12 16:49:31 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_delete_node(t_env **env, t_env *node)
{
	t_env	*tmp;

	tmp = *env;
	if (!(*env))
		return ;
	if (*env == node)
	{
		free(node->var);
		free(node->value);
		*env = (*env)->next;
		free(node);
	}
	else
	{
		while (tmp && tmp->next != node)
			tmp = tmp->next;
		tmp->next = node->next;
		free(node->var);
		free(node->value);
		free(node);
	}
}

void	ft_unset(t_env **env, char **argv)
{
	int		i;
	t_env	*tmp;

	i = 1;
	while (argv[i])
	{
		tmp = *env;
		while (tmp)
		{
			if (ft_strcmp(argv[i], tmp->var) == 0)
			{
				ft_delete_node(env, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

void	ft_unset_export_no_fork(t_lexer **args, t_env **env, int old)
{
	char	**argv;

	if (count_pipe(*args) > 0)
		return ;
	argv = ft_command(*args);
	if (!argv)
		return ;
	if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(env, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
	{
		ft_export(env, argv);
	}
	else if (ft_strcmp(argv[0], "exit") == 0)
	{
		ft_free_parser_lexer(*args);
		*args = NULL;
		ft_exit(argv, *env, old);
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(argv + 1, env);
	ft_free_split(argv);
	argv = NULL;
}
