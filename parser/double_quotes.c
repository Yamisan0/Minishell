/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:55:35 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:17:51 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	double_quote_validity_check(t_lexer *head)
{
	t_lexer	*tmp;
	int		nb;

	nb = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->token == DOUBLE_QUOTE && tmp->str[0] == '\"')
			nb++;
		tmp = tmp->next;
	}
	if (nb % 2 != 0)
		return (1);
	return (0);
}

int	single_quote_state(t_lexer *head)
{
	t_lexer	*tmp;
	int		len;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == SINGLE_QUOTE && tmp->state == DEFAULT)
		{
			len = ft_strlen(tmp->str);
			if (len == 1)
				return (0);
			if (len > 2 && (tmp->str[0] != '\'' || tmp->str[len - 1] != '\''))
				return (0);
			if (len == 2 && tmp->str[1] == '\"')
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	quote_pars(t_lexer *head)
{
	if (single_quote_state(head) == 0)
		return (ft_printf(
				"minishell: syntax error near unexpected simple quote\n"), 0);
	if (double_quote_validity_check(head) == 1)
		return (ft_printf(
				"minishell: syntax error near unexpected double quote\n"), 0);
	return (1);
}
