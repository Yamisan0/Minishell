#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

int ft_parser(t_lexer *head)
{
    if (double_quote_state(head) == 0 || single_quote_state(head) == 0)
        return (printf("PROBLEME DE QUOTE\n"), 0);
    return (1);
}