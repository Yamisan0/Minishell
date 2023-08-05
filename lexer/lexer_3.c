#include "../includes/minishell.h"



void	delete_spaces(t_lexer *head)
{
	t_lexer *tmp;
	t_lexer *stock;

	tmp = head;
	while (tmp)
	{
		if (tmp && tmp->token == WHITE_SPACE && tmp->state == DEFAULT)
		{
			stock = tmp;
			tmp = tmp->next;
			if (stock->str)
				free(stock->str);
			ft_destroy_node(stock);
			continue;
		}
			tmp = tmp->next;
	}
}

void	ft_word(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (is_special_token(tmp) == 0 && tmp->token != WHITE_SPACE)
			tmp->token = WORD;
		tmp = tmp->next;
	}
}
void	fusion_reste(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == WORD)
		{
			if (tmp->next && tmp->next->token != WHITE_SPACE &&
				!is_special_token(tmp->next) && tmp->next == DEFAULT)
			{
				tmp->str = alloc_strcat(tmp->str, tmp->next->str);
				ft_destroy_node(tmp->next);
				continue;
			}
		}
		tmp = tmp->next;
	}
}

void	fusion_words(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->next && tmp->token == WORD && tmp->next->token == WORD)
		{
			tmp->str = alloc_strcat(tmp->str, tmp->next->str);
			ft_destroy_node(tmp->next);
			continue;
		}
		tmp = tmp->next;
	}
}







