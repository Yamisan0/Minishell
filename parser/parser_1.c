#include "../includes/minishell.h"

void	set_redirection_type(t_lexer *head)
{
	t_lexer *tmp;
	
	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, ">>", ft_strlen(tmp->str)) == 0)
			tmp->token = DOUT;
		if (ft_strncmp(tmp->str, ">", ft_strlen(tmp->str)) == 0)
			tmp->token = OUT;
		if (ft_strncmp(tmp->str, "<", ft_strlen(tmp->str)) == 0)
			tmp->token = IN;
		if (ft_strncmp(tmp->str, "<<", ft_strlen(tmp->str)) == 0)
			tmp->token = DIN;
		tmp = tmp->next;
	}
}

void	ft_set_to_cmd(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->i == 0 && tmp->token == WORD)
		tmp = tmp->next;
	}
}

void	ft_set_infile_outfile(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == OUT || tmp->token == DOUT)
			if (tmp->next && tmp->next->token == WORD)
				tmp->next->token = OUTFILE;
		if (tmp->token == IN || tmp->token == DIN)
			if (tmp->next && tmp->next->token == WORD)
				tmp->next->token = INFILE;
		tmp = tmp->next;
	}
}

