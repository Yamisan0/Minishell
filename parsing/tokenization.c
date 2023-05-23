#include "../includes/minishell.h"

int is_a_token(char c)
{
	if (c == '>' || c == '<'  || c == '|')
		return (1);
	return (0);
}

void	create_token_node(char *word, t_lexer **head, char *token)
{
	t_lexer *new;
	t_lexer *ptr;

	ptr = *head;
	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		return ;
	new->str = word;
	if (!(*head))
		*head = new;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
	while ()
}