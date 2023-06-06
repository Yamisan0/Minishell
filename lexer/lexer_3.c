#include "../includes/lexer_parser.h"
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
			if (tmp->next && tmp->next->token != WHITE_SPACE && !is_special_token(tmp->next) && tmp->next == DEFAULT)
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

t_lexer *ft_lexer(char *prompt)
{
	t_lexer	*lexer;

	if (!prompt)
		return (NULL);
	lexer = pre_lexing(prompt);
	big_lexer(lexer);
	set_state_quotes(lexer);
	single_quote_fusion(lexer);
	return (lexer);
}
void	ft_lexer_part_2(t_lexer *lexer, t_env *env)
{
	ft_word(lexer);
	fusion_words(lexer);
	fusion_reste(lexer);
	delete_spaces(lexer);
	ft_fusion_double_quotes(lexer);
	dollar_lexer(lexer);
	ft_replace_by_litteral(lexer, env);
}