#include "../includes/minishell.h"
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
			if ((tmp->prev && is_special_token(tmp->prev))
					|| (tmp->next && is_special_token(tmp->next)))
				return (-1);
			if (tmp->next == NULL)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_print_error(int indice, char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (indice == 1)
		write(2, &str, 2);
	write(2, "\n", 1);
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
				return (ft_print_error(1, tmp->str + 2), -1);
			if (tmp->next && is_special_token(tmp->next) && ft_strlen(tmp->next->str) > 1)
				return (printf("minishell : syntax error near unexpected token `%s'\n", tmp->next->str + ft_strlen(tmp->next->str) - 2), -1);
			if (tmp->next && is_special_token(tmp->next))
				return (printf("minishell : syntax error near unexpected token `%s'\n", tmp->next->str), -1);
			if (tmp->next == NULL)
				return (printf("minishell : syntax error near unexpected token `newline'\n"), -1);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_heredoc_tokens(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->prev && tmp->token == DIN && tmp->next
			&& tmp->next->token == WORD)
		{
			tmp->prev->token = HEREDOC;
			tmp->next->token = DELIMITER;
		}
		tmp = tmp->next;
	}
}

int ft_parser(t_lexer *head)
{
	if (valid_pipe(head) == -1)
		return (ft_free_parser_lexer(head), write(2, "minishell: syntax error near unexpected token `|'\n", 50) -1);
	if (valid_simple_redirection(head) == -1)
		return (ft_free_parser_lexer(head), -1);
	set_redirection_type(head);
	ft_set_infile_outfile(head);
	ft_heredoc_tokens(head);
	return (1);
}

void	num_args(t_lexer *head)
{
	int	i;
	t_lexer *tmp;

	i = 0;
	tmp = head;
	while (tmp)
	{
		tmp->i = i;
		i++;
		tmp = tmp->next;
	}
}

char *ft_argv(t_lexer *head, int i)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->i == i)
			return (tmp->str);
		tmp = tmp->next;
	}
	return (NULL);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}