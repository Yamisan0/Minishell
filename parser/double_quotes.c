#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

void    set_state_quotes(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == DOUBLE_QUOTE)
		{
			while (tmp && tmp->token != DOUBLE_QUOTE)
			{
				tmp->state = OPENED;
				tmp = tmp->next;
			}
			if (tmp->next->token == DOUBLE_QUOTE)
				tmp->state = OPENED;
			continue;
			
		}
		tmp = tmp->next;
	}
}
