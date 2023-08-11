/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:03:10 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 17:39:04 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	size_tab(t_lexer *head)
{
	t_lexer	*tmp;
	int		size;

	size = 0;
	tmp = head;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == WORD)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

void	ft_norm_command(char **tab, t_lexer *tmp, int *i)
{
	tab[*i] = ft_strdup(tmp->str);
	(*i)++;
}

char	**ft_command(t_lexer *head)
{
	t_lexer	*tmp;
	char	**tab;
	int		i;
	int		passed;

	passed = 0;
	i = size_tab(head);
	if (i == 0)
		return (NULL);
	tmp = head;
	tab = ft_calloc(i + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == WORD && tmp->str[0] != '\0')
			passed = 1;
		if (tmp->token == WORD && passed == 1)
			ft_norm_command(tab, tmp, &i);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**get_entire_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!ft_strnstr(envp[i], "PATH", 4))
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}
