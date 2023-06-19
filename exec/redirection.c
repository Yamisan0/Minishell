#include "../includes/minishell.h"

int open_files(int  indice, char *path, t_exec *ptr)
{
	int fd;

	if (indice == 1)
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_free_all("minishell", ptr);
	}
	else if (indice == 2)
	{
		fd = open(path, O_WRONLY | O_CREAT, 0666);
		if (fd == -1)
			ft_free_all("minishell", ptr);
	}
	else if (indice == 3)
	{
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			ft_free_all("minishell", ptr);
	}
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
			ptr->redirect = OUT;
			return (tmp);
		}
		if (tmp->token == OUTFILE && tmp->prev->token == DOUT)
		{
			ptr->redirect = DOUT;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_open(t_lexer *head, t_exec *ptr)
{
	int fd;
	(void)ptr;

	if (!head)
		return (-1);
	if (ptr->redirect == IN)
	{
		fd = open_files(1, head->str, ptr);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("minishell");
	}
	if (ptr->redirect == OUT)
	{
		fd = open_files(2, head->str, ptr);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("minishell");	
	}
	if (ptr->redirect == DOUT)
	{
		fd = open_files(3, head->str, ptr);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("minishell");
	}
	close (fd);
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
	// while (tmp)
	// {
		if (ft_open(tmp, ptr) == -1)
			return (-1);
	// 	tmp = ft_next_redirection(tmp->next, ptr);
	// }
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
