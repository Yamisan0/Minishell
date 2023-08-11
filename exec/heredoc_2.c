/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:09:00 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 17:54:23 by akdjebal         ###   ########.fr       */
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

void	ft_error_heredoc(char *s1, char *s2, char *delimiter, char *s3)
{
	char	to_print[1000];

	ft_strlcpy(to_print, s1, 1000);
	ft_strlcat(to_print, s2, 1000);
	ft_strlcat(to_print, delimiter, 1000);
	ft_strlcat(to_print, s3, 1000);
	write(2, &to_print, ft_strlen(to_print));
}

void	ft_norn_heredoc(char *delimiter)
{
	if (g_ecode != 130)
		ft_error_heredoc("minishell: warning: here-document delimited",
			" by end-of-file (wanted `", delimiter, "')\n");
}

char	*ft_get_heredoc(char *delimiter)
{
	char	*prompt;
	char	*heredoc;

	prompt = NULL;
	heredoc = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		if (g_ecode != 130)
			prompt = readline("heredoc>");
		if (!prompt || g_ecode == 130)
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
