/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:53:26 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 14:54:47 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*c_to_str(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	return (str);
}

t_lexer	*new_node(char *str)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		return (NULL);
	if (!str)
	{
		free(new);
		return (NULL);
	}
	new->str = str;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*ft_add_back_lex(t_lexer *head, t_lexer *new)
{
	t_lexer	*tmp;

	if (!head)
		return (new);
	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->prev == NULL)
		{	
			tmp->prev = head;
			head = tmp;
		}
	}
	tmp->next = new;
	new->prev = tmp;
	return (head);
}

void	ft_destroy_node(t_lexer *node_to_delete)
{
	if (!node_to_delete->next)
	{
		node_to_delete->prev->next = NULL;
		free(node_to_delete);
	}
	else
	{
		node_to_delete->prev->next = node_to_delete->next;
		node_to_delete->next->prev = node_to_delete->prev;
		free(node_to_delete);
	}
}

char	*alloc_strcat(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
	{
		while (s1[++i])
			str[i] = s1[i];
	}
	if (s2)
	{
		while (s2[++j])
		{
			str[i] = s2[j];
			i++;
		}
	}
	free(s1);
	free(s2);
	return (str);
}
