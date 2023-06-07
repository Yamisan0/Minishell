#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

void    dollar_lexer_3(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp->next)
	{
		if (tmp->token == DOLLAR && tmp->next->token == ALPHA_NUM 
				&& ft_strlen(tmp->str) == 1)
		{
			tmp->str = alloc_strcat(tmp->str, tmp->next->str);
			ft_destroy_node(tmp->next);
			tmp->dollar = COMPLEX;
			continue;
		}
		tmp = tmp->next;
	}
}

void    dollar_lexer_2(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp->next)
	{
		if (tmp->token == DOLLAR && tmp->next->token == INTERRO
				&& ft_strlen(tmp->str) == 1 && ft_strlen(tmp->next->str) == 1)
		{
			tmp->str = alloc_strcat(tmp->str, tmp->next->str);
			ft_destroy_node(tmp->next);
			tmp->dollar = COMPLEX;
			continue;
		}
		tmp = tmp->next;
	}
}

void    dollar_lexer(t_lexer *head)
{
	t_lexer *tmp;

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
			continue;
		}
		tmp = tmp->next;
	}
	dollar_lexer_2(head);
	dollar_lexer_3(head);
}
