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

int	ft_redirections(t_exec *ptr)
{
	t_lexer	*tmp;
	int		fd;

	tmp = ptr->data->args;
	// while (tmp && tmp->token == PIPE)
	// {
		if (tmp->token == IN)
		{
			fd = open_files(1, tmp->next->str);
			dup2(fd, STDIN_FILENO);
			// if (fd == -1)
			// 	return (0);
			// dup2(fd, STDIN_FILENO);
			// close(fd);
		}
	// 	tmp = tmp->next;
	// }
	return (1);
}