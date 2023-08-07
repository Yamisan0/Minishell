#include "../includes/minishell.h"

void	close_fds(int *fd_tab, int prev_fd)
{
	close(fd_tab[0]);
	close(fd_tab[1]);
	if (prev_fd != -1)
		close(prev_fd);
}
int 	ft_forking(t_exec *ptr, int i, t_env *env)
{
	int	builtin;

	if (set_exec(ptr, i, env) == -1)
		return (close_fds(ptr->fd, ptr->prev), -1);
	if (dup_close_fd_pipe(ptr, i) == -1)
		return (-1);
	if (ft_redir(ptr) == -1)
		return (-1);
	builtin = ft_built_in(ptr->full_cmd, env, ptr->tmp);
	if (builtin == -1 && ptr->path && ptr->full_cmd && ptr->env)
	{
		free_env(ptr->data->env);
		ptr->data->env = NULL;
		execve(ptr->path, ptr->full_cmd, ptr->env);
	}
	ft_free_all(NULL, ptr);
	return (1);
}


void	ft_main_process(t_exec *ptr)
{
	close(ptr->fd[1]);
	if (ptr->prev != -1)
		close(ptr->prev);
	ptr->prev = ptr->fd[0];
}

void	ft_free_process(t_exec *ptr)
{
	ft_free_split(ptr->env);
	free_env(ptr->data->env);
	ptr->data->env = NULL;
	free(ptr->pid);
	ft_free_split(ptr->full_cmd);
	ft_free_parser_lexer(ptr->data->args);
	free(ptr->data);
	free(ptr);
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
				close_fds(ptr->fd, ptr->prev);
			if (ft_forking(ptr, i, ptr->data->env) != 1)
				return (ft_free_process(ptr), exit(exit_code), -1);
			exit(exit_code);
		}
		else if (ptr->pid[i] > 0)
			ft_main_process(ptr);
		i++;
	}
	close(ptr->prev);
	wait_all_pids(ptr);
	free(ptr->pid);
	return (1);
}
