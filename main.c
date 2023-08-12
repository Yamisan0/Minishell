/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:40:02 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/12 15:51:25 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_ecode = 0;

t_mini	*init_mini(t_lexer *head, t_env *env)
{
	t_mini	*ptr;
	char	**heredoc;

	(void)env;
	if (!head)
		return (NULL);
	ptr = ft_calloc(1, sizeof(t_mini));
	if (!ptr)
		return (NULL);
	ptr->args = head;
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, ft_handler_heredoc);
	heredoc = get_heredoc_tab(head);
	ptr->tab_heredoc = fill_heredoc_tab(heredoc, head);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	ptr->nb_pipe = ft_nb_pipe(head);
	ptr->exec = init_exec(ptr);
	ptr->exec->data = ptr;
	ptr->env = env;
	return (ptr);
}

t_lexer	*ft_parser_lexer(char *prompt, t_env *env)
{
	t_lexer	*head;

	head = ft_lexer(prompt);
	if (!head)
		return (NULL);
	if (quote_pars(head) == 0)
		return (free(prompt), ft_free_parser_lexer(head), NULL);
	if (ft_lexer_part_2(head, env) == -1)
		return (free(prompt), ft_free_parser_lexer(head), NULL);
	if (ft_parser(head) == -1)
		return (free(prompt), ft_free_parser_lexer(head), NULL);
	return (free(prompt), head);
}

void	ft_norm_main(t_mini *minish, char *prompt)
{
	if (g_ecode == 130)
	{
		ft_free_minishell_struct(minish, prompt, 130);
		return ;
	}
	signal(SIGINT, ft_handler_exec);
	signal(SIGQUIT, ft_handler_exec);
	ft_pipex(minish->exec);
	ft_free_minishell_struct(minish, prompt, 0);
}

int	ft_norm_main_part_2(char **av)
{
	(void)av;
	// if (isatty(STDIN_FILENO) == 0)
	// 	return (0);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*list;
	char	*prompt;
	t_mini	*minish;
	t_env	*minishell_env;

	minishell_env = set_env(envp);
	if (ac == 1)
	{
		while (42)
		{
			if (ft_norm_main_part_2(av) == 0)
				return (free_env(minishell_env), 0);
			prompt = ft_prompt(minishell_env);
			if (prompt == NULL)
				continue ;
			list = ft_parser_lexer(prompt, minishell_env);
			g_ecode = 0;
			if (!list)
				continue ;
			ft_unset_export_no_fork(&list, &minishell_env);
			minish = init_mini(list, minishell_env);
			if (minish)
				ft_norm_main(minish, prompt);
		}
	}
}
