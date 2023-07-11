#include "../includes/minishell.h"

void	set_index_env(t_env	*env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

t_env   *create_node(char *str_to_cpy)
{
	t_env	*node;
	int		i;
	int		j;

	i = 0;
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	while (str_to_cpy[i] && str_to_cpy[i] != '=')
		i++;
	j = i + 1;
	while (str_to_cpy[j])
		j++;
	node->var = ft_calloc(i + 1, sizeof(char));
	node->value = ft_calloc((j - i) + 1, sizeof(char));
	return (node);
}

void	cpy_tab(char *str, t_env *node)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!node)
		return ;
	while (str[i] && str[i] != '=')
	{
		node->var[i] = str[i];
		i++;
	}
	str[i] = '\0';
	j = i + 1;
	while (str[j])
	{
		node->value[k] = str[j];
		j++;
		k++;
	}
	node->value[k] = '\0';
}

t_env	*add_to_list(t_env *head, t_env *new_node)
{
	t_env	*tmp;

	tmp = head;
	if (!head)
		return (new_node);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}

t_env	*set_env(char **envp)
{
	int		i;
	t_env	*head = NULL;
	t_env	*new;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		new = create_node(envp[i]);
		cpy_tab(envp[i], new);
		head = add_to_list(head, new);
		i++;
	}
	set_index_env(head);
	return (head);
}

int		ft_print_env(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		printf("%s=%s\n", env->var, env->value);
		env = env->next;
	}
	return (1);
}
