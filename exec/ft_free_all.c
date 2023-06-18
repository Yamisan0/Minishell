#include "../includes/minishell.h"


void	ft_free_parser_lexer(t_lexer *pile)
{
	t_lexer	*tmp;

	tmp = pile;
	while (pile)
	{
		pile = pile->next;
		free(tmp->str);
		free(tmp);
		tmp = pile;
	}
}

void    ft_free_all(char *msg)
{
    perror(msg);
}