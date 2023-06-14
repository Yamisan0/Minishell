#include "../includes/minishell.h"


void	free_2darray(char	**split)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (split[size])
		size++;
	while (i < size)
		free(split[i++]);
	free(split);
	split = NULL;
}

char **ft_command(t_lexer *head)
{
	t_lexer *tmp;
	char    **tab;
	int     i;
	i = 0;
	tmp = head;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == WORD)
			i++;
		tmp = tmp->next;
	}
	tmp = head;
	tab = ft_calloc(i + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == WORD)
		{
			tab[i] = ft_strdup(tmp->str);
			i++;
		}
		tmp = tmp->next;
	}
	return (tab);
}

char	*check_slash(char *command)
{
	if (ft_strchr(command, '/') && access(command, F_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

char	**get_entire_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*path(char *command, char **envp)
{
	char	**entire_path;
	char	*command_path;
	char	*add_slash;
	int		i;

	i = 0;
	if (ft_strchr(command, '/'))
		return (check_slash(command));
	entire_path = get_entire_path(envp);
	while (entire_path[i])
	{
		add_slash = ft_strjoin(entire_path[i], "/");
		command_path = ft_strjoin(add_slash, command);
		free(add_slash);
		if (access(command_path, F_OK) == 0)
		{
			free_2darray(entire_path);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free_2darray(entire_path);
	return (NULL);
}
