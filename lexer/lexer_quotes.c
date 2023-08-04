#include "../includes/minishell.h"

void    single_quote_fusion(t_lexer *head)
{
	t_lexer	*travel;

	travel = head;
	while (travel)
	{
		if (travel->token == SINGLE_QUOTE && travel->state == DEFAULT)
		{
			while (travel->next && travel->next->token != SINGLE_QUOTE)
			{
				travel->str = alloc_strcat(travel->str, travel->next->str);
				ft_destroy_node(travel->next);
			}
			if ( travel->next && travel->token == SINGLE_QUOTE)
			{
				travel->str = alloc_strcat(travel->str, travel->next->str);
				ft_destroy_node(travel->next);
			}
		}
		travel = travel->next;
	}
}

void	ft_supp_simple_quotes(t_lexer * head)
{
	t_lexer *tmp;
	char	*str;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == SINGLE_QUOTE && tmp->state == DEFAULT)
		{
			str = ft_calloc(ft_strlen(tmp->str + 1), sizeof(char));
			if (!str)
				return ;
			ft_strlcpy(str, tmp->str + 1, ft_strlen(tmp->str + 1));
			free(tmp->str);
			tmp->str = str;
		}
		tmp = tmp->next;
	}
}

void    double_quote_fusion(t_lexer *head)
{
	
	t_lexer	*travel;

	travel = head;
	while (travel)
	{
		if (travel->token == DOUBLE_QUOTE)
		{
			while (travel->next && travel->next->token != DOUBLE_QUOTE)
			{
				travel->str = alloc_strcat(travel->str, travel->next->str);
				ft_destroy_node(travel->next);
			}
				if ( travel->next && travel->token == DOUBLE_QUOTE)
				{
					travel->str = alloc_strcat(travel->str, travel->next->str);
					ft_destroy_node(travel->next);
				}
		}
		travel = travel->next;
	}
}

void	ft_supp_double_quotes(t_lexer * head)
{
	t_lexer *tmp;
	char	*str;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == DOUBLE_QUOTE && tmp->state == OPENED)
		{
			str = ft_calloc(ft_strlen(tmp->str + 1), sizeof(char));
			if (!str)
				return ;
			ft_strlcpy(str, tmp->str + 1, ft_strlen(tmp->str + 1));
			free(tmp->str);
			tmp->str = str;
		}
		tmp = tmp->next;
	}
}

void    set_state_quotes(t_lexer *head)
{
	t_lexer *tmp;
	t_lexer	*stock;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == DOUBLE_QUOTE)
		{
			stock = tmp;
			while (tmp)
			{
				tmp->state = OPENED;
				if (tmp->token == DOUBLE_QUOTE && tmp != stock)
					break;
				tmp = tmp->next;
			}
		}
		if (tmp == NULL)
			continue;
		tmp = tmp->next;
	}
}
