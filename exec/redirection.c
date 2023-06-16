#include "../includes/minishell.h"

int open_files(int  indice, char *path)
{
	int fd;

	if (indice == 1)
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_free_all("minishell");
	}
	else if (indice == 2)
	{
		fd = open(path, O_WRONLY | O_CREAT, 0666);
		if (fd == -1)
			ft_free_all("minishell");
	}
	else if (indice == 3)
	{
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			ft_free_all("minishell");
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
		if (tmp->token == IN)
		{
			ptr->redirect = IN;
			return (tmp->next);
		}
		if (tmp->token == OUT)
		{
			ptr->redirect = OUT;
			return (tmp->next);
		}
		if (tmp->token == DOUT)
		{
			ptr->redirect = DOUT;
			return (tmp->next);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_open(t_lexer *head, t_exec *ptr)
{
	int fd;

	if (ptr->redirect == IN)
	{
		fd = open_files(1, head->str);
		dup2(fd, STDIN_FILENO);
		close (fd);
	}
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

void	ft_redir(t_exec *ptr)
{
	t_lexer *tmp;

	tmp = ft_next_redirection(ptr->tmp, ptr);
	while (tmp && tmp->token != PIPE)
	{
		if (is_redirection(tmp))
		{
			ft_open(tmp, ptr);
			tmp = ft_next_redirection(tmp, ptr);
		}
		tmp = tmp->next;
	}
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

// int	ft_redirections(t_exec *ptr)
// {
// 	t_lexer	*tmp;
// 	int		fd;
	
// 	// tmp = ft_next_redirection(ptr,);
// 	if (!tmp)
// 		return (0);
// 	fd = open_files(1, tmp->next->str);
// 	dup2(fd, STDIN_FILENO);
// 	return (1);
// }