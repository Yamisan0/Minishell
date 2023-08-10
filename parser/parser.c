#include "../includes/minishell.h"

int valid_pipe(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			if (!tmp->prev)
				return (-1);
			if (ft_strlen(tmp->str) > 1)
				return (-1);
			if ((tmp->prev && tmp->prev->token == PIPE)
				|| (tmp->next && tmp->next->token == PIPE))
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
			if (ft_strlen(tmp->str) > 2)
				return (ft_printf("minishell : syntax error near unexpected token `%s'\n",
							tmp->str + ft_strlen(tmp->str) - 2), -1);
			if (tmp->next && is_special_token(tmp->next) && ft_strlen(tmp->next->str) > 1)
				return (ft_printf("minishell : syntax error near unexpected token `%s'\n",
							tmp->next->str + ft_strlen(tmp->next->str) - 2), -1);
			if (tmp->next && is_special_token(tmp->next))
				return (ft_printf(
							"minishell : syntax error near unexpected token `%s'\n", tmp->next->str), -1);
			if (tmp->next == NULL)
				return (ft_printf(
							"minishell : syntax error near unexpected token `newline'\n"), -1);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_heredoc_tokens(t_lexer *head)
{
	t_lexer *tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->token == DIN && tmp->next && tmp->next->token == WORD)
		{
			tmp->next->token = DELIMITER;
			tmp->next->index_heredoc = i;
			i++;
		}
		tmp = tmp->next;
	}
}


int ft_parser(t_lexer *head)
{
	if (valid_pipe(head) == -1)
		return (ft_printf(
					"minishell: syntax error near unexpected token `|'\n"), -1);
	if (valid_simple_redirection(head) == -1)
		return (-1);
	set_redirection_type(head);
	ft_set_infile_outfile(head);
	return (1);
}




