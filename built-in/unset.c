#include "../includes/minishell.h"

void	ft_delete_node(t_env *env, t_env *node)
{
	t_env	*tmp;

	tmp = env;
	free(node->var);
	free(node->value);
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	tmp->next = node->next;
	free(node);
}

int ft_unset(t_env *env, char *var)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var) == 0)
		{
			ft_delete_node(env, tmp);
		}
		tmp = tmp->next;
	}
	return (1);
}


void	ft_unset_export_no_fork(t_lexer *args, t_env *env)
{
	t_lexer *tmp;
	int		i;
	char	**argv;

	i = 0;
	tmp = ret_next_pipe(args, i);
	while (tmp)
	{
		argv = ft_command(tmp);
		if (ft_strcmp(argv[0], "unset") == 0)
			ft_unset(env, argv[1]);
		i++;
		tmp = ret_next_pipe(args, i);
		ft_free_split(argv);
	}
}
