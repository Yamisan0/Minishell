#include "../includes/minishell.h"


char	*ft_strcat_env(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 2), sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	str[i] = '=';
	i++;
	if (s2)
		while (s2[++j])
		{
			str[i] = s2[j];
			i++;
		}
	str[i] = '\0';
	return (str);
}


char **create_envp(t_env *env)
{
	t_env *tmp;
	char    **array;
	int     len;
	int		i;

	i = 0;
	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	array = ft_calloc(len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	tmp = env;
	while (i <= len && tmp)
	{
		array[i] = ft_strcat_env(tmp->var, tmp->value);
		tmp = tmp->next;
		i++;
	}
	array[len] = NULL;
	return (array);
}

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int count_pipe(t_lexer *head)
{
	t_lexer *tmp;
	int		nb_pipe;

	nb_pipe = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->token == PIPE)
			nb_pipe++;
		tmp = tmp->next;
	}
	return (nb_pipe);
}

void    wait_all_pids(t_exec *args)
{
	int		i;

	i = 0;
	while (i < (args->data->nb_pipe + 1))
	{
		waitpid(args->pid[i], NULL, 0);
		i++;
	}
}

//calcule le nombre de pipe
//x