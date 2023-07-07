#include "../includes/minishell.h"

t_env	*delete_node_env(t_env *env, t_env *node)
{
	t_env *tmp;

	tmp = env;
	if (env == node)
		return (free(node->value), free(node->var), free(node), NULL);
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	if (node->next == NULL)
		tmp->next == NULL;
	if (node->next)
		tmp->next = node->next;
		return (free(node->value), free(node->var), free(node), env);
}

int ft_unset(t_env *env, char *var)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var) == 0)
		{
			env = delete_node_env(env, tmp);
		}
		tmp = tmp->next;
	}
}
