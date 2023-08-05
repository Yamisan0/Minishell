#include "../includes/minishell.h"


int		write_expand(char *str, int fd, t_env *env)
{
	char	var[10000];
	char	*value;
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[1] == '$' || ft_strlen(str) == 1)
		return (write(fd, "$", 1), 1);
	if ( str[1] && str[1] == '?')
	{
		value = ft_itoa(exit_code);
		ft_putstr_fd(value, fd);
		return (2);
	}
	while (str[i] && str[i] != ' ' && str[i] != '$' && ft_isalnum(str[i]))
		i++;
	ft_strlcpy(var, str + 1, i);
	value = ft_give_val(env, var);
	if (!value)
		return (i);
	ft_putstr_fd(value, fd);
	return (i);
}

char	**get_heredoc_tab(t_lexer *head)
{
	t_lexer	*tmp;
	int		i;
	char	**tab;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->token == DELIMITER)
		{
			tmp->index_heredoc = i;
			i++;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		return (NULL);
	tab = ft_calloc(i + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (tab);
}


void	ft_write_in_file(char *str_doc, int fd, t_env *env)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	if (!str_doc)
		return ;
	tab = ft_split(str_doc, '\n');
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '$')
			{
				j =  j + write_expand(tab[i] + j, fd, env);
				continue;
			}
			write(fd, &tab[i][j], 1);
			j++;
		}
		write(fd, "\n", 1);
		i++;
	}
	ft_free_split(tab);
}

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
			break;
		}
		heredoc = fusion_heredoc(prompt, heredoc);
	}
	return (heredoc);
}


char	**fill_heredoc_tab(char **tab, t_lexer *head)
{
	int	i;
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
