#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

int	double_quote_validity_check(t_lexer *head)
{
	t_lexer *tmp;
	int		nb;

	nb = 1;
	tmp = head;
	while (tmp)
	{
		if (tmp->token == DOUBLE_QUOTE)
			nb++;
		tmp = tmp->next;
	}
	if (nb % 2 == 0 || nb == 0)
		return (1);
	return (0);
}


int	single_quote_state(t_lexer *head)
{
	t_lexer *tmp;
	int		len;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == SINGLE_QUOTE)
		{
			if (tmp->state == OPENED)
				continue;
			len = ft_strlen(tmp->str);
			if (len == 1)
				return (0);
			if (!(len > 1 && tmp->str[0] == '\'' && tmp->str[len - 1] == '\''))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}