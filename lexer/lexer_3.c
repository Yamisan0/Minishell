#include "../includes/lexer_parser.h"
#include "../includes/minishell.h"

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
void    single_quote_fusion(t_lexer *head)
{
	
	t_lexer	*travel;

	travel = head;
	while (travel)
	{
		if (travel->token == SINGLE_QUOTE)
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

t_lexer *ft_lexer(char *prompt)
{
	t_lexer	*lexer;

	if (!prompt)
		return (NULL);
	lexer = pre_lexing(prompt);
	big_lexer(lexer);
	double_quote_fusion(lexer);
	single_quote_fusion(lexer);
	dollar_lexer(lexer);
	return (lexer);
}
