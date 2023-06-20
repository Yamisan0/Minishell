#include "../includes/minishell.h"

int open_files(int  indice, char *path)
{
	int fd;

	if (indice == 1)
		fd = open(path, O_RDONLY);
	else if (indice == 2)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (indice == 3)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
	return (fd);
}

void	ft_cpy_std(t_exec *ptr)
{
	ptr->sstdin = dup(STDIN_FILENO);
	ptr->sstdout = dup(STDOUT_FILENO);
}

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

int	ft_open(t_lexer *head, t_exec *ptr)
{
	if (!head)
		return (-1);
	if (ptr->redirect == IN)
	{
		if (ft_open_n_dup(1, head, ptr) == -1)
			return (-1);
	}
	if (ptr->redirect == OUT)
	{
		if (ft_open_n_dup(2, head, ptr) == -1)
			return (-1);
	}
	if (ptr->redirect == DOUT)
	{
		if (ft_open_n_dup(3, head, ptr) == -1)
			return (-1);
	}
	return (1);
}

int	is_redirection(t_lexer *node)
{
	if ((node->token == IN || node->token == OUT || node->token == DOUT)
			&& node->redirection == NOT)
	{
		node->redirection = VISITED;
		return (1);
	}
	return (0);
	
}

int	ft_redir(t_exec *ptr)
{
	t_lexer *tmp = NULL;

	tmp = ft_next_redirection(ptr->tmp, ptr);
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (ft_open(tmp, ptr) == -1)
			return (perror("minishell"), -1);
		tmp = ft_next_redirection(tmp->next, ptr);
	// 	if (!tmp)
	// 		break;
	}
	return (1);
}

int	count_in(t_lexer *head)
{
	t_lexer *tmp;
	int		count;

	tmp = head;
	count = 0;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == IN)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
