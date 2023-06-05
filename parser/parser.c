#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

int valid_pipe(t_lexer *head)
{
    t_lexer *tmp;

    tmp = head;
    while (tmp)
    {
        if (tmp->token == PIPE)
        {
            if (ft_strlen(tmp->str) > 1)
            return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

int valid_simple_redirection(t_lexer *head)
{
    t_lexer *tmp;

    tmp = head;
    while (tmp)
    {
        if (tmp->token == REDIRECTION_RIGHT || tmp->token == REDIRECTION_LEFT)
        {
            if (ft_strlen(tmp->str) > 2)
                return (printf("minishell : syntax error near unexpected token '%s'\n", tmp->str + ft_strlen(tmp->str) - 2), 0);
        }
        tmp = tmp->next;
    }
    return (1);
}

int ft_parser(t_lexer *head)
{
    if (single_quote_state(head) == 0 || double_quote_validity_check(head) == 1)
        return (printf("PROBLEME DE QUOTE\n"), -1);
    if (valid_pipe(head) == -1)
        return (printf("syntax error near unexpected token '|'\n") -1);
    if (valid_simple_redirection(head) == 0)
        return (-1);
    
    return (1);
}