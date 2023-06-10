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
t_lexer *ft_lexer(char *prompt)
{
	t_lexer	*lexer;

	if (!prompt)
		return (NULL);
	lexer = pre_lexing(prompt);
	big_lexer(lexer);
	single_quote_fusion(lexer);
	set_state_quotes(lexer);
	dollar_lexer(lexer);
	return (lexer);
}

void	ft_lexer_part_2(t_lexer *lexer, t_env *env)
{
	ft_replace_by_litteral(lexer, env);
	ft_supp_simple_quotes(lexer);
	double_quote_fusion(lexer);
	ft_supp_double_quotes(lexer);
	ft_word(lexer);
	fusion_words(lexer);
	delete_spaces(lexer);
}