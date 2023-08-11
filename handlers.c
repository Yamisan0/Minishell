/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:39:33 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:39:44 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_handler_heredoc(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		exit_code = 130;
		rl_done = 1;
	}
	else if (i == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

void	ft_handler(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handler_exec(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit_code = 130;
	}
	else if (i == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n");
	}
}
