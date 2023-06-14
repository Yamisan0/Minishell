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
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			if (count_pipe == i)
				return (tmp->next);
			count_pipe++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void 	ft_forking(t_exec *ptr, int i)
{
	t_lexer	*tmp;
	char	**full_cmd;
	char	*cmd;
	char	*path;
	char	**env;

	tmp = ret_next_pipe(ptr->data->args, i);
	full_cmd = ft_command(tmp);
	cmd = full_cmd[0];
	env = create_envp(global_env);
	path = ft_path(cmd, env);
	if (i == 0 && ptr->data->nb_pipe > 0)
	{
		if (dup2(ptr->fd[1], STDOUT_FILENO) == -1)
			perror("minishell");
	}
	else if (i > 0 && i < ptr->data->nb_pipe + 1)
	{
		if (dup2(ptr->prev, STDIN_FILENO) == -1)
			perror("minishell");
		close(ptr->prev);
		if (dup2(ptr->fd[1], STDOUT_FILENO))
			perror("minishell");
	}
	if (i == ptr->data->nb_pipe + 1)
	{
		if (dup2(ptr->prev, STDIN_FILENO) == -1)
			perror("minishell");
	}
	execve(path, full_cmd, env);
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