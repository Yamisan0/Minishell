#include "../includes/minishell.h"

t_lexer *ft_next_redirection(t_lexer *head, t_exec *ptr)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == DELIMITER)
		{
			ptr->redirect = HEREDOC;
			return (tmp);
		}
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
			return (ft_printf("minishell: %s: %s\n",
						head->str, strerror(errno)), exit_code = 1, -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return(perror("minishell"), close(fd), -1);
	}
	close(fd);
	return (1);
}

