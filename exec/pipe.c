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

int	set_exec(t_exec *ptr, int i, t_env *env)
{
	ptr->tmp = ret_next_pipe(ptr->data->args, i);
	ptr->full_cmd = ft_command(ptr->tmp);
	if (ptr->full_cmd)
	{
		ptr->cmd = ptr->full_cmd[0];
		ptr->env = create_envp(env);
		ptr->path = ft_path(ptr->cmd, ptr->env);
		if (ft_check_builtin(ptr->full_cmd) == -1 && !ptr->path) //check aussi si PATH existe, s'il existe il faut modifier l'erreur affichee en no such file or directory
		{
			ptr->path_split = get_entire_path(ptr->env);
			write(2, "minishell: ", 11);
			ft_putstr_fd(ptr->cmd, 2);
			if (!ptr->path_split)
				write(2, ": No such file or directory\n", 28);
			else
			{
				ft_free_split(ptr->path_split);
				write(2, ": command not found\n", 20);
			}
			exit_code = 127;
			return (-1);
		}
	}
	return (1);
}

int	dup_close_fd_pipe(t_exec *ptr, int i)
{
	close(ptr->fd[0]);
	if (i == 0 && ptr->data->nb_pipe > 0)
	{
		if (dup2(ptr->fd[1], STDOUT_FILENO) == -1)
			return (-1);
		close(ptr->fd[1]);
	}
	else if (i != ptr->data->nb_pipe)
	{
		if (dup2(ptr->prev, STDIN_FILENO) == -1)
			return (-1);
		close(ptr->prev);
		if (dup2(ptr->fd[1], STDOUT_FILENO) == -1)
			return (-1);
		close(ptr->fd[1]);
	}
	if (i == ptr->data->nb_pipe && i > 0)
	{
		if (dup2(ptr->prev, STDIN_FILENO) == -1)
			return (-1);
		close(ptr->prev);
	}
	return (1);
}

void dupg(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}
int 	ft_forking(t_exec *ptr, int i, t_env *env)
{
	int	builtin;

	if (set_exec(ptr, i, env) == -1)
		return (-1);
	if (dup_close_fd_pipe(ptr, i) == -1)
		return (exit_code = errno, -1);
	if (ft_redir(ptr) == -1)
		return (exit_code = errno, -1);
	builtin = ft_built_in(ptr->full_cmd, env, ptr->tmp);
	exit_code = 0;
	if (builtin == -1 && ptr->path && ptr->full_cmd && ptr->env)
		execve(ptr->path, ptr->full_cmd, ptr->env);
	ft_free_all(NULL, ptr);
	exit(0);
	return (1);
}


int	ft_pipex(t_exec *ptr)
{
	int	i;

	i = 0;
	while (i < (ptr->data->nb_pipe + 1))
	{
		pipe(ptr->fd);
		ptr->pid[i] = fork();
		if (ptr->pid[i] == 0)
		{
			if (ptr->data->nb_pipe == 0)
			{
				close(ptr->fd[1]);
				close(ptr->fd[0]);
			}
			if (ft_forking(ptr, i, ptr->data->env) != 1)
				return (free(ptr->pid), exit(0), -1);
		}
		else if (ptr->pid[i] > 0)
		{
			close(ptr->fd[1]);
			if (ptr->prev != -1)
				close(ptr->prev);
			ptr->prev = ptr->fd[0];
		}
		i++;
	}
	close(ptr->prev);
	wait_all_pids(ptr);
	free(ptr->pid);
	return (1);
}
