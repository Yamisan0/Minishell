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

int	ft_redir(t_exec *ptr)
{
	t_lexer *tmp = NULL;
	int in = dup(0);
	int out = dup(1);
	tmp = ft_next_redirection(ptr->tmp, ptr);
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (ft_open(tmp, ptr) == -1)
			return (dupclosestd(in, out), perror("minishell"), -1);
		tmp = ft_next_redirection(tmp->next, ptr);
	// 	if (!tmp)
	// 		break;
	}
	dupclosestd(in, out);
	return (1);
}

