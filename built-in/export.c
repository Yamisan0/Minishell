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

t_env		*ft_check_exist(t_env *env, char *arg)
{
	t_env	*tmp;
	char	var_name[100];
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	ft_strlcpy(var_name, arg, i + 1);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var_name, tmp->var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char *return_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (arg + i + 1);
		i++;
	}
	return (NULL);
}

void	ft_add_back_export(t_env **env, t_env *new_node)
{
	t_env *tmp;

	tmp = *env;
	if (!tmp)
		*env = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	ft_export(t_env **env, char **argv)
{
	t_env	*tmp;
	t_env	*head;

	head = *env;
	tmp = *env;
	int	i;
	i = 1;
	while (argv[i])
	{
		tmp = ft_check_exist(*env, argv[i]);
		if (tmp)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(return_equal(argv[i]));
			printf("%s=%s\n", tmp->var, tmp->value);
		}
		else
		{
			tmp = create_node(argv[i]);
			cpy_tab(argv[i], tmp);
			head = add_to_list(head, tmp);
		}
		i++;
	}
	*env = head;
}
