#include "../includes/lexer_parser.h"
#include "../includes/minishell.h"

char	*ft_give_val(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, name, ft_strlen(name)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}