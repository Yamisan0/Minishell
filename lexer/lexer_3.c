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
	dollar_lexer(lexer);
	return (lexer);
}

void	ft_supp_double_quotes(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if ((tmp->prev && tmp->state == OPENED && tmp->prev->state == DEFAULT && tmp->str[0] == '\"') || (tmp->next && tmp->state == OPENED && tmp->next->state == DEFAULT && tmp->str[0] == '\"'))
		{
			free(tmp->str);
			ft_destroy_node(tmp);
		}
		if ((tmp->prev == NULL || tmp->next == NULL )&& (tmp->state == OPENED))
		{
			free(tmp->str);
			ft_destroy_node(tmp);
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
		if (tmp->token == SINGLE_QUOTE)
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

void	ft_lexer_part_2(t_lexer *lexer, t_env *env)
{
	ft_replace_by_litteral(lexer, env);
	//ft_retirer_quotes
	ft_supp_simple_quotes(lexer);
	ft_supp_double_quotes(lexer);
	//fusionner deux maillons qui ne font pas parti des  caracteres speciaux et qui ne sont pas separes par un espace

	ft_fusion_double_quotes(lexer);
	ft_word(lexer);
	fusion_words(lexer);
	fusion_reste(lexer);
	delete_spaces(lexer);
}