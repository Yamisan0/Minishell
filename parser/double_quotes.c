#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

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
