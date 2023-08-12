/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:25:22 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/12 15:35:34 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dollar_lexer_3(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp->next)
	{
		if (tmp->token == DOLLAR && tmp->next->token == ALPHA_NUM
			&& ft_strlen(tmp->str) == 1)
		{
			tmp->str = alloc_strcat(tmp->str, tmp->next->str);
			ft_destroy_node(tmp->next);
			tmp->dollar = COMPLEX;
			continue ;
		}
		tmp = tmp->next;
	}
}

void	dollar_lexer_2(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp->next)
	{
		if (tmp->token == DOLLAR && tmp->next->token == INTERRO
			&& ft_strlen(tmp->str) == 1 && ft_strlen(tmp->next->str) == 1)
		{
			tmp->str = alloc_strcat(tmp->str, tmp->next->str);
			ft_destroy_node(tmp->next);
			tmp->dollar = COMPLEX;
			continue ;
		}
		tmp = tmp->next;
	}
}

void	dollar_lexer(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		if (tmp->token == DOLLAR && tmp->next->token == DOLLAR
			&& ft_strlen(tmp->str) == 1 && ft_strlen(tmp->next->str) == 1)
		{
			tmp->str = alloc_strcat(tmp->str, tmp->next->str);
			ft_destroy_node(tmp->next);
			tmp->dollar = COMPLEX;
			continue ;
		}
		tmp = tmp->next;
	}
	dollar_lexer_2(head);
	dollar_lexer_3(head);
}

void	ft_set_index_pipe(t_lexer *lexer)
{
	t_lexer	*tmp;
	int		index;

	index = 1;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			tmp->index_pipe = index;
			tmp = tmp->next;
			while (tmp && tmp->token != PIPE)
			{
				tmp->index_pipe = index;
				tmp = tmp->next;
			}
			index++;
			continue;
		}
		tmp = tmp->next;
	}
}
