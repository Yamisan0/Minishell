/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:15:05 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/12 15:58:52 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_files(int indice, char *path, char *name)
{
	int	fd;

	if (indice == 1)
		fd = open(path, O_RDONLY);
	else if (indice == 2)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (indice == 3)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (indice == 4)
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (indice == 5)
		fd = open(name, O_RDONLY);
	return (fd);
}

int	ft_open_dup_heredoc(t_lexer *head, t_exec *ptr)
{
	int		fd;
	char	name[50];
	char	*nbr;

	nbr = ft_itoa(head->index_pipe);
	ft_strlcpy(name, ".minishell_heredoc", 30);
	ft_strlcat(name, nbr, 50);
	free(nbr);
	fd = open_files(4, "", name);
	if (fd == -1)
		return (perror("minishell"), -1);
	ft_write_in_file(ptr->data->tab_heredoc[head->index_heredoc],
		fd, ptr->data->env);
	close(fd);
	fd = open_files(5, "", name);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("minishell"), close(fd), unlink(name), -1);
	close(fd);
	return (unlink(name), 1);
}

int	ft_open(t_lexer *head, t_exec *ptr)
{
	if (!head)
		return (-1);
	if (ptr->redirect == IN)
	{
		if (ft_open_n_dup(1, head, ptr) == -1)
			return (ft_printf("minishell: %s: %s\n",
					head->str, strerror(errno)), g_ecode = 1, -1);
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
