/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:39:33 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/12 17:02:29 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_handler_heredoc(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		g_ecode = 130;
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
		g_ecode = 130;
	}
	else if (i == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n");
	}
}

t_lexer	*ft_norm_main_part3(char *prompt, t_env *minishell_env, int *old)
{
	t_lexer	*list;

	list = ft_parser_lexer(prompt, minishell_env);
	(*old) = g_ecode;
	g_ecode = 0;
	return (list);
}


