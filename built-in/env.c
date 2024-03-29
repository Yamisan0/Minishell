/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:51:07 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:05:07 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_index_env(t_env	*env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

t_env	*create_node(char *str_to_cpy)
{
	t_env	*node;
	int		i;
	int		j;

	i = 0;
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	while (str_to_cpy[i] && str_to_cpy[i] != '=')
		i++;
	j = i + 1;
	if (str_to_cpy[i] == '=')
	{
		while (str_to_cpy[j])
			j++;
	}
	node->var = ft_calloc(i + 1, sizeof(char));
	if (str_to_cpy[i] == '=')
		node->value = ft_calloc((j - i) + 1, sizeof(char));
	else
		node->value = NULL;
	return (node);
}

void	cpy_tab(char *str, t_env *node)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!node)
		return ;
	while (str[i] && str[i] != '=')
	{
		node->var[i] = str[i];
		i++;
	}
	if (str[i] == '=')
	{
		j = i + 1;
		while (str[j])
		{
			node->value[k] = str[j];
			j++;
			k++;
		}
	}
}

t_env	*add_to_list(t_env *head, t_env *new_node)
{
	t_env	*tmp;

	tmp = head;
	if (!head)
		return (new_node);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}

t_env	*set_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*new;

	head = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		new = create_node(envp[i]);
		cpy_tab(envp[i], new);
		head = add_to_list(head, new);
		i++;
		new = NULL;
	}
	set_index_env(head);
	return (head);
}
