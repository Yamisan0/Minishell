#include "../includes/minishell.h"

t_env *ft_delete_node(t_env *env, t_env *node)
{
	t_env	*tmp;

	tmp = env;
	free(node->var);
	free(node->value);
	if (tmp != node)
	{
		
		while (tmp && tmp->next != node)
			tmp = tmp->next;
		tmp->next = node->next;
		return (free(node), env);
	}
	else
	{
		env = env->next->next;
		free(node);
	}
	return (env);
}



int ft_unset(t_env *env, char **argv, t_mini *ptr)
{
	int		i;
	t_env	*tmp;

	i = 1;
	while (argv[i])
	{
		tmp = env;
		while (tmp)
		{
			if (ft_strcmp(argv[i], tmp->var) == 0)
			{
				ptr->env = ft_delete_node(env, tmp);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (1);
}


void	ft_unset_export_no_fork(t_lexer *args, t_env *env, t_mini *ptr)
{
	char	**argv;

	argv = ft_command(args);
	if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(env, argv, ptr);
}
