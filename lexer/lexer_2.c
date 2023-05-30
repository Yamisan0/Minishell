#include "../includes/lexer.h"

void    ft_free_parsed_prompt(t_lexer *list)
{
    t_lexer *tmp;

    if (!list)
        return ;
    tmp = list;
    tmp = tmp->next;
    while (tmp)
    {
        free(list);
        list = tmp;
        tmp = tmp->next;
    }
}