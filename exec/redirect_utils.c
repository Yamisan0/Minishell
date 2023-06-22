#include "../includes/minishell.h"

t_lexer *ft_next_redirection(t_lexer *head, t_exec *ptr)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == INFILE)
		{
			ptr->redirect = IN;
			return (tmp);
		}
		if (tmp->token == OUTFILE)
		{
			ptr->redirect = tmp->prev->token;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_open_n_dup(int indice, t_lexer *head, t_exec *ptr)
{
	int fd;
	(void)ptr;

	if (indice == 1)
	{
		fd = open_files(1, head->str);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return(perror("minishell"), close(fd), -1);
	}
	else if (indice > 1)
	{
		fd = open_files(indice, head->str);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return(perror("minishell"), close(fd), -1);
	}
	close(fd);
	return (1);
}

void	dupclosestd(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}