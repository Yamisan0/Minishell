/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:12:40 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 14:12:48 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_close_fd_pipe(t_exec *ptr, int i)
{
	close(ptr->fd[0]);
	if (i == 0 && ptr->data->nb_pipe > 0)
	{
		if (dup2(ptr->fd[1], STDOUT_FILENO) == -1)
			return (close(ptr->fd[1]), -1);
		close(ptr->fd[1]);
	}
	else if (i != ptr->data->nb_pipe)
	{
		if (dup2(ptr->prev, STDIN_FILENO) == -1)
			return (close(ptr->prev), -1);
		close(ptr->prev);
		if (dup2(ptr->fd[1], STDOUT_FILENO) == -1)
			return (close(ptr->fd[1]), -1);
		close(ptr->fd[1]);
	}
	if (i == ptr->data->nb_pipe && i > 0)
	{
		close(ptr->fd[1]);
		if (dup2(ptr->prev, STDIN_FILENO) == -1)
			return (close(ptr->prev), -1);
		close(ptr->prev);
	}
	return (1);
}
