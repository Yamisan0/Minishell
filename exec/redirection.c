/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:15:05 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:12:49 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_files(int indice, char *path)
{
	int	fd;

	if (indice == 1)
		fd = open(path, O_RDONLY);
	else if (indice == 2)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (indice == 3)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (indice == 4)
		fd = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (indice == 5)
		fd = open("tmp.txt", O_RDONLY);
	return (fd);
}

int	ft_open_dup_heredoc(t_lexer *head, t_exec *ptr)
{
	int	fd;

	fd = open_files(4, "");
	if (fd == -1)
		return (perror("minishell"), -1);
	ft_write_in_file(ptr->data->tab_heredoc[head->index_heredoc],
		fd, ptr->data->env);
	close(fd);
	fd = open_files(5, "");
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("minishell"), close(fd), -1);
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
			return (ft_printf("minishell: %s: %s\n", head->str, strerror(errno)), exit_code = 1, -1);
	}
	else if (ptr->redirect == OUT)
	{
		if (ft_open_n_dup(2, head, ptr) == -1)
			return (-1);
	}
	else if (ptr->redirect == DOUT)
	{
		if (ft_open_n_dup(3, head, ptr) == -1)
			return (-1);
	}
	else if (ptr->redirect == HEREDOC)
	{
		if (ft_open_dup_heredoc(head, ptr) == -1)
			return (-1);
	}
	return (1);
}

int	ft_redir(t_exec *ptr)
{
	t_lexer	*tmp;

	tmp = NULL;
	tmp = ft_next_redirection(ptr->tmp, ptr);
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (ft_open(tmp, ptr) == -1)
			return (-1);
		tmp = ft_next_redirection(tmp->next, ptr);
	}
	return (1);
}
