#include "../includes/minishell.h"

t_exec  *init_exec(t_mini *ptr)
{
	t_exec	*exe;

	exe = ft_calloc(1, sizeof(t_exec));
	if (!exe)
		return (NULL);
	exe->pid = ft_calloc(ptr->nb_pipe + 1, sizeof(pid_t));
	exe->prev = -1;
	return (exe);
}

t_lexer	*ret_next_pipe(t_lexer *head, int i)
{
	t_lexer *tmp;
	int		count_pipe;

	count_pipe = 0;
	tmp = head;
	if (i == 0)
		return (head);
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			count_pipe++;
			if (count_pipe == i)
				return (tmp->next);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_norm_exec(t_exec *ptr)
{
	ft_free_split(ptr->path_split);
	ft_write_error("minishell: ", ptr->cmd, ": command not found\n");
}

int	ft_check_directory(char *str)
{
	struct stat stats;
	int			var;

	var = 0;
	if (!str)
		return (1);
	if ((str[0] && str[1] && str[0] == '.' && str[1] == '/')
			|| (str[0] && str[0] == '/') || str[ft_strlen(str + 1)] == '/')
		var = 1;
	if (stat(str, &stats) == -1)
		return (1);
	if (S_ISDIR(stats.st_mode) && var == 1)
	{
		ft_printf("minishell: %s: Is a directory\n", str);
		exit_code = 126;
		return (-1);
	}
	return (1);
}



int	set_exec(t_exec *ptr, int i, t_env *env)
{
	ptr->tmp = ret_next_pipe(ptr->data->args, i);

	ptr->full_cmd = ft_command(ptr->tmp);
	if (ptr->full_cmd)
	{
		ptr->cmd = ptr->full_cmd[0];
		ptr->env = create_envp(env);
		ptr->path = ft_path(ptr->cmd, ptr->env);
		if (ft_check_directory(ptr->cmd) == -1)
			return (free(ptr->path), -1);
		if (ft_check_builtin(ptr->full_cmd) == -1 && !ptr->path)
		{
			ptr->path_split = get_entire_path(ptr->env);
			if (!ptr->path_split || ft_strchr(ptr->cmd, '/'))
				return (ft_free_split(ptr->path_split),
							ft_write_error("minishell: ", ptr->cmd, ": No such file or directory\n")
								, exit_code = 127, -1);
			else
				ft_norm_exec(ptr);
			exit_code = 127;
			return (-1);
		}
	}
	return (1);
}



