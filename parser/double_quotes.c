#include "../includes/minishell.h"

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

int	quote_pars(t_lexer *head)
{
	if (single_quote_state(head) == 0)
		return (write(1, "minishell: syntax error near unexpected simple quote\n", 52), 0);
	if (double_quote_validity_check(head) == 1)
		return (write(1, "minishell: syntax error near unexpected double quote\n", 52), 0);
	return (1);
}