#include "../includes/minishell.h"

void	ft_export_sans_arg(t_env *env)
{
	t_env   *tmp;
	if (!env)
		return ;
	tmp = env;
	while (tmp)
	{
		printf("export %s=\"%s\"", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}

t_env		*ft_check_exist(t_env *env, char *var)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
}

char *return_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (arg + i);
	}
	return (NULL);
}

void	ft_export(t_env *env, char **argv)
{
	t_env	*tmp;

	int	i;
	i = 1;
	while (argv[i])
	{
		tmp = ft_check_exist(env, argv[i]);
		if (tmp)
		{
			
		}
		i++;
	}
}
