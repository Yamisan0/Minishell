#include "../includes/minishell.h"
#include "../includes/lexer_parser.h"

int	is_special_token(t_lexer *node)
{
	if (node->token == PIPE || node->token == REDIRECTION_LEFT || node->token == REDIRECTION_RIGHT)
		return (1);
	return (0);
}

int valid_pipe(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			if (ft_strlen(tmp->str) > 1)
				return (-1);
			if ((tmp->prev && is_special_token(tmp->prev)) || (tmp->next && is_special_token(tmp->next)))
				return (-1);
			if (tmp->next == NULL)
				return (-1);
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
			if (tmp->next == NULL || tmp->next->next == NULL)
				return (printf("minishell : syntax error near unexpected token 'newline'\n"), -1);
			if (ft_strlen(tmp->str) > 2)
				return (printf("minishell : syntax error near unexpected token '%s'\n", tmp->str + ft_strlen(tmp->str) - 2), -1);
			if (tmp->next && is_special_token(tmp->next) && ft_strlen(tmp->next->str) > 1)
				return (printf("minishell : syntax error near unexpected token '%s'\n", tmp->next->str + ft_strlen(tmp->next->str) - 2), -1);
			if (tmp->next && is_special_token(tmp->next))
				return (printf("minishell : syntax error near unexpected token '%s'\n", tmp->next->str), -1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int ft_parser(t_lexer *head)
{
	if (valid_pipe(head) == -1)
		return (printf("syntax error near unexpected token '|'\n") -1);
	if (valid_simple_redirection(head) == -1)
		return (-1);
	
	return (1);
}