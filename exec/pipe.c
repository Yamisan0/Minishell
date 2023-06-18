#include "../includes/minishell.h"

t_exec  *init_exec(t_mini *ptr)
{
	t_exec	*exe;

	exe = ft_calloc(1, sizeof(t_exec));
	if (!exe)
		return (NULL);
	exe->pid = ft_calloc(ptr->nb_pipe + 1, sizeof(pid_t));
	exe->prev = -1;
	// exe->fd_in = ft_calloc(ptr->nb_in, sizeof(int));
	// exe->fd_out = ft_calloc(ptr->nb_out, sizeof(int));
	return (exe);
}

int	dup_close(int fd1, int fd2)
{
		if (dup2(fd1, fd2) == -1)
			return (perror("minishell"), -1);
		else
			close(fd1);
		return (1);
}

t_lexer	*ret_next_pipe(t_lexer *head, int	i)
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

int	set_exec(t_exec *ptr, int i)
{
	ptr->tmp = ret_next_pipe(ptr->data->args, i);
	
	ptr->full_cmd = ft_command(ptr->tmp);
	ptr->cmd = ptr->full_cmd[0];
	ptr->env = create_envp(global_env);
	ptr->path = ft_path(ptr->cmd, ptr->env);
	if (!ptr->path)
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(ptr->cmd, 2);
		write(2, ": command not found\n", 20);
		errno = 127;
		return (0);
	}
	return (1);
}

int	dup_close_fd_pipe(t_exec *ptr, int i)
{
	close(ptr->fd[0]);
	if (i == 0 && ptr->data->nb_pipe > 0)
	{
		if (dup2(ptr->fd[1], STDOUT_FILENO) == -1)
			return (ft_free_all("minishell"), 0);
		close(ptr->fd[1]);
	}
	else if (i != ptr->data->nb_pipe)
	{
		if (dup2(ptr->prev, STDIN_FILENO) == -1)
			return (ft_free_all("minishell"), 0);
		if (dup2(ptr->fd[1], STDOUT_FILENO) == -1)
			return (ft_free_all("minishell"), 0);
		close(ptr->fd[1]);
	}
	if (i == ptr->data->nb_pipe && i > 0)
	{
		if (dup2(ptr->prev, STDIN_FILENO) == -1)
			return (ft_free_all("minishell"), 0);
	}
	return (1);
}

void 	ft_forking(t_exec *ptr, int i)
{
	if (set_exec(ptr, i) == 0)
		return ;
	// dup_close_fd_pipe(ptr, i);
	ft_redir(ptr);
	execve(ptr->path, ptr->full_cmd, ptr->env);
}

void    wait_all_pids(t_exec *args)
{
	int		i;

	i = 0;
	while (i <= (args->data->nb_pipe + 1))
	{
		waitpid(args->pid[i], NULL, 0);
		i++;
	}
}

void	ft_pipex(t_exec *ptr)
{
	int	i;

	i = 0;
	while (i <= (ptr->data->nb_pipe + 1))
	{
		pipe(ptr->fd);
		ptr->pid[i] = fork();
		if (ptr->pid[i] == 0)
			ft_forking(ptr, i);
		else if (ptr->pid[i] > 0)
		{
			close(ptr->fd[1]);
			if (ptr->prev != -1)
				close(ptr->prev);
			ptr->prev = ptr->fd[0];
		}
		i++;
	}
	wait_all_pids(ptr);
	free(ptr->pid);
}




// pas besoin de stocker les fd dans un tableau
// faire fonction qui dup2 toutes les redirections d'entrees
// d'un pipe a un autre et faire un autre fonction qui 
// reinitialise le stdin a chaque pipe