#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

int ft_parser(t_lexer *head)
{
    if (single_quote_state(head) == 0 || double_quote_validity_check(head) == 1)
        return (printf("PROBLEME DE QUOTE\n"), 0);
    return (1);
}