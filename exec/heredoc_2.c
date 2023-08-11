/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:09:00 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 15:10:31 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fusion_heredoc(char *prompt, char *heredoc)
{
	char	*tmp;
	char	*tmp_stock;
	char	*tmp_heredoc;

	tmp_stock = ft_strdup(prompt);
	tmp = ft_strjoin(tmp_stock, "\n");
	free(tmp_stock);
	if (!heredoc)
		heredoc = ft_strjoin("", tmp);
	else
	{
		tmp_heredoc = heredoc;
		heredoc = ft_strjoin(tmp_heredoc, tmp);
		free(tmp_heredoc);
	}
	free(tmp);
	free(prompt);
	return (heredoc);
}

void	ft_norn_heredoc(char *delimiter)
{
	if (exit_code != 130)
		ft_printf(
			"minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
			delimiter);
}

char	*ft_get_heredoc(char *delimiter)
{
	char	*prompt;
	char	*heredoc;

	prompt = NULL;
	heredoc = NULL;
	while (1)
	{
		if (exit_code != 130)
			prompt = readline("heredoc>");
		if (!prompt || exit_code == 130)
		{
			ft_norn_heredoc(delimiter);
			free(prompt);
			prompt = NULL;
			return (free(heredoc), NULL);
		}
		if (ft_strcmp(prompt, delimiter) == 0)
		{
			free(prompt);
			break ;
		}
		heredoc = fusion_heredoc(prompt, heredoc);
	}
	return (heredoc);
}

char	**fill_heredoc_tab(char **tab, t_lexer *head)
{
	int		i;
	t_lexer	*tmp;

	if (!tab)
		return (NULL);
	tmp = head;
	i = 0;
	while (tmp)
	{
		if (tmp->token == DELIMITER)
		{
			tab[i] = ft_get_heredoc(tmp->str);
			i++;
		}
		tmp = tmp->next;
	}
	return (tab);
}
