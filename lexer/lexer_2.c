#include "../includes/lexer_parser.h"

void free_lex_list(t_lexer *head)
{
	t_lexer *current = head;
	t_lexer *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void    ft_destroy_node(t_lexer *node_to_delete)
{
	if (!node_to_delete->next)
	{
		node_to_delete->prev->next = NULL;
		free(node_to_delete);
	}
	else
	{
		node_to_delete->prev->next = node_to_delete->next;
		node_to_delete->next->prev = node_to_delete->prev;
		free(node_to_delete);
	}
}

char *alloc_strcat(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
	{
	while (s1[++i])
		str[i] = s1[i];
	}
	if (s2)
	{
		while (s2[++j])
		{
			str[i] = s2[j];
			i++;
		}
	}
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

void    big_lexer(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	if (!head)
		return ;
	while (head->next != NULL)
	{
		while (head->next)
		{
			if (head->token == head->next->token &&
					head->token != DOUBLE_QUOTE && head->token != SINGLE_QUOTE
					 && head->token != DOLLAR)
			{
				head->str = alloc_strcat(head->str, head->next->str);
				ft_destroy_node(head->next);
				break;
			}
			head = head->next;
		}
		if (head->next != NULL)
			head = tmp;
	}
}

void	ft_fusion_double_quotes(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->next && tmp->state == OPENED && tmp->next->state == OPENED)
		{
			tmp->str = alloc_strcat(tmp->str, tmp->next->str);
			ft_destroy_node(tmp->next);
			continue;
		}
		tmp = tmp->next;
	}
}
