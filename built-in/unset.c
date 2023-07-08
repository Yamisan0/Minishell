#include "../includes/minishell.h"

void	ft_delete_node(t_env **env, t_env *node)
{
	t_env	*tmp;

	tmp = *env;
	free(node->var);
	free(node->value);
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	printf("%s111\n", tmp->next->var);
	tmp->next = node->next;
	printf("%s222\n",node->next->var);
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
			ft_delete_node(&env, tmp);
		}
		tmp = tmp->next;
	}
	return (1);
}
