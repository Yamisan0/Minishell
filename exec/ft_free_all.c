#include "../includes/minishell.h"

void    ft_free_parser_lexer(t_lexer *head)
{
    t_lexer *tmp;
    
    if (!head)
        return ;
    tmp = head->next;
    while (tmp)
    {
        if (head->str)
            free(head->str);
        free(head);
        head = tmp;
        tmp = tmp->next;
    }
}

void    ft_free_all(char *msg)
{
    perror(msg);
}