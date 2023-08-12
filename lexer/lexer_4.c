#include "../includes/minishell.h"

int	next_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}


void	ft_add_node_middle(t_lexer *node, t_lexer *new)
{
	if (node->str[0] == ' ')
	{
		node->str = ft_strdup(" ");
		node->token = WHITE_SPACE;
	}
	new->prev = node;
	new->next = node->next;
	node->next = new;
	if (new->next)
		new->next->prev = new;
}

char	*get_new_str(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	result = ft_calloc(i + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, i + 1);
	return (result);
}

void	ft_modify_lexer(t_lexer *node, char **tab)
{
	int	i;
	t_lexer	*new;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		if (i == 0)
		{
			tmp = node->str;
			node->str = get_new_str(tmp);
			free(tmp);
		}
		else
		{
			new = new_node(" ");
			ft_add_node_middle(node, new);
			node = node->next;
			new = new_node(tab[i]);
			ft_add_node_middle(node, new);
			node = node->next;
		}
		i++;
	}
}

int	ft_len_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void    check_after_expand(t_lexer *lexer)
{
	t_lexer *tmp;
	char	**tab;
	int		skip;

	skip = 0;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->dollar == COMPLEX && tmp->token != DOUBLE_QUOTE)
		{
			if (next_space(tmp->str) == 1)
			{
				tab = ft_split_charset(tmp->str, " \t");
				ft_modify_lexer(tmp, tab);
				while (skip++ <= ft_len_split(tab))
					tmp = tmp->next;
				skip = 0;
				continue;
			}
		}
		tmp = tmp->next;
	}
}
