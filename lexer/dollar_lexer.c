/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:25:22 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:15:38 by akdjebal         ###   ########.fr       */
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
