/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:56:32 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:18:43 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_give_val(t_env *env, char *name)
{
	t_env	*tmp;
	char	str_vide[] = "";

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(str_vide));
}

void	ft_replace_by_litteral(t_lexer *head, t_env *env)
{
	t_lexer	*tmp;
	char	*stock;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == DOLLAR && tmp->dollar == COMPLEX
			&& get_token_type(tmp->str[1]) == ALPHA_NUM)
		{
			stock = tmp->str;
			tmp->str = ft_give_val(env, tmp->str + 1);
			free(stock);
		}
		else if (tmp->token == DOLLAR && tmp->dollar == COMPLEX && tmp->str[1] == '?')
		{
			stock = tmp->str;
			tmp->str = ft_itoa(exit_code);
			free(stock);
		}
		tmp = tmp->next;
	}
}
