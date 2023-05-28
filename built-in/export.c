#include "../includes/minishell.h"

void	export(char *var, char *value, t_env *env)
{
	t_env	*tmp;
	t_env	*new;

	while (tmp)
	{
		if (ft_strncmp(var, tmp->var, sizeof(tmp)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
	add_to_list(env, new);
}
