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
			if ((tmp->next && is_special_token(tmp->next)) || (tmp->prev && is_special_token(tmp->prev)))
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
			if (ft_strlen(tmp->str) > 2)
				return (printf("minishell : syntax error near unexpected token '%s'\n", tmp->str + ft_strlen(tmp->str) - 2), 0);
			if (tmp->next && tmp->next->token == WHITE_SPACE && tmp->next->next->token == PIPE)
				return (printf("minishell : syntax error near unexpected token '%s'\n",tmp->str), ft_strlen(tmp->str) - 2, 0);
			if (tmp->next && tmp->token != tmp->next->token && (tmp->next->token == REDIRECTION_LEFT || tmp->next->token == REDIRECTION_RIGHT))
				return (printf("minishell : syntax error near unexpected token '%s'\n", tmp->next->str + ft_strlen(tmp->next->str) - 2), 0);
			if (tmp->next->next && (tmp->next->next->token == REDIRECTION_LEFT || tmp->next->next->token == REDIRECTION_LEFT) && tmp->next->token == WHITE_SPACE)
				return (printf("minishell : syntax error near unexpected token '%s'\n",
							tmp->next->next->str + ft_strlen(tmp->next->next->str) - 2), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

// int valid

int ft_parser(t_lexer *head)
{
	if (single_quote_state(head) == 0 || double_quote_validity_check(head) == 1)
		return (printf("PROBLEME DE QUOTE\n"), -1);
	if (valid_pipe(head) == -1)
		return (printf("syntax error near unexpected token '|'\n") -1);
	// if (valid_simple_redirection(head) == 0)
	// 	return (-1);
	
	return (1);
}