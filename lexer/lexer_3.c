#include "../includes/lexer.h"
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
