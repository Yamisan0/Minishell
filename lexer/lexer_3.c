#include "../includes/lexer.h"
#include "../includes/minishell.h"

int	check_two_quotes(char *str)
{
	if (ft_strlen(str) != 0 && (str[0] == ' '&& str[ft_strlen(str)] == ' '))
		return (1);
	return (0);
}

void    double_quote_fusion(t_lexer *head)
{
	
	t_lexer	*travel;

	travel = head;
	while (travel)
	{
		if (travel->token == DOUBLE_QUOTE && check_two_quotes(travel->str) == 0)
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
