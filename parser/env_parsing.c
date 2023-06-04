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

void	ft_replace_by_litteral(t_lexer *head, t_env *env)
{
	t_lexer	*tmp;
	char	*stock;

	tmp = head;
	while (tmp)
	{
		if (tmp->token == DOLLAR && tmp->dollar == COMPLEX && get_token_type(tmp->str[1]) == ALPHA_NUM)
		{
			stock = tmp->str;
			tmp->str = ft_give_val(env, tmp->str + 1);
			free(stock);
		}
		if (tmp->token == DOLLAR && tmp->dollar == COMPLEX && tmp->str[1] == '?')
		{
			stock = tmp->str;
			tmp->str = ft_give_val(env, "SYSTEMD_EXEC_PID");
		}
		tmp = tmp->next;
	}
}
