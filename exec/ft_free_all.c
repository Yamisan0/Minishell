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

void    ft_free_all(char *msg, t_exec *ptr)
{
	dupclosestd(ptr);
	if (ptr->full_cmd)
		ft_free_split(ptr->full_cmd);
	if (ptr->full_cmd)
		ft_free_split(ptr->env);
	free(ptr->path);
	ptr->tmp = NULL;
	// ft_free_parser_lexer(ptr->data->args);
    if (msg)
		perror(msg);
}