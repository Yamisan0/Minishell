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



int ft_unset(t_env *env, char **argv)
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
				ft_delete_node(env, tmp);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (1);
}


void	ft_unset_export_no_fork(t_lexer *args, t_env *env)
{
	char	**argv;

	argv = ft_command(args);
	if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(env, argv);
}
