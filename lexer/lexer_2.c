#include "../includes/lexer.h"

void free_lex_list(t_lexer *head)
{
	t_lexer *current = head;
	t_lexer *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}
