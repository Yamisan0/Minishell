#include "../includes/minishell.h"

void	free_2darray(char **split)
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

char	*check_slash(char *command)
{
	if (ft_strchr(command, '/') && access(command, F_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

char	*ft_path_norm(char **big_path)
{
	ft_free_split(big_path);
	return (NULL);
}

char	*ft_path(char *command, char **envp)
{
	char	**entire_path;
	char	*command_path;
	char	*add_slash;
	int		i;

	i = 0;
	if (ft_strchr(command, '/'))
		return (check_slash(command));
	entire_path = get_entire_path(envp);
	if (!entire_path)
		return (NULL);
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
	return (ft_path_norm(entire_path));
}