#include "../includes/minishell.h"


void	ft_heredoc(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
	}
}

int		write_expand(char *str, int fd)
{
	char	var[1000];
	char	*value;
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[1] == '$' || ft_strlen(str) == 1)
		return (write(fd, "$", 1), 1);
	if ( str[1] && str[1] == '?')
	{
		value = ft_itoa(errno);
		ft_putstr_fd(value, fd);
		return (2);
	}
	while (str[i] && str[i] != ' ' && str[i] != '$' && ft_isalnum(str[i]))
		i++;
	ft_strlcpy(var, str + 1, i);
	value = ft_give_val(global_env, var);
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
			i++;
		tmp = tmp->next;
	}
	if (i == 0)
		return (NULL);
	tab = ft_calloc(i + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (tab);
}


void	ft_write_in_file(char *str_doc, int fd)
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
				j =  j + write_expand(tab[i] + j, fd);
				continue;
			}
			write(fd, &tab[i][j], 1);
			j++;
		}
		write(fd, "\n", 1);
		i++;
	}
}

char	*ft_get_heredoc(char *delimiter)
{
	char	*prompt = NULL;
	char	*heredoc = NULL;
	char	*tmp;

	while (1)
	{
		prompt = readline("heredoc>");
		if (ft_strcmp(prompt, delimiter) == 0)
			break;
		tmp = ft_strdup(prompt);
		tmp = ft_strjoin(tmp, "\n");
		if (!heredoc)
			heredoc = ft_strjoin("", tmp);
		else
			heredoc = ft_strjoin(heredoc, tmp);
		free(tmp);
		free(prompt);
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
