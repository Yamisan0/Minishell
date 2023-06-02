#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

void    dollar_lexer(t_lexer *head)
{
    t_lexer *tmp;

    tmp = head;
    while (tmp->next)
    {
        if (tmp->token == DOLLAR && tmp->next->token == ALPHA_NUM)
        {
            tmp->str = alloc_strcat(tmp->str, tmp->next->str);
            ft_destroy_node(tmp->next);
            continue;
        }
        tmp = tmp->next;
    }
}