#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

void    set_state_quotes(t_lexer *head)
{
    t_lexer *tmp;
    int     nb;

    tmp = head;
    nb = 0;
    while (tmp)
    {
        if (tmp->token == DOUBLE_QUOTE)
        {
            nb++;
            tmp->state = OPENED;
        }
        if (nb == 2)
            nb = 0;
        tmp = tmp->next;
    }
}