#include "../includes/minishell.h"
#include "../includes/lexer.h"

char *c_to_str(char c)
{
	char *str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
t_lexer	*new_node(char *str)
{
	t_lexer *new;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		return (NULL);
	if (!str)
		return (NULL);
	new->str = str;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer *ft_add_back_lex(t_lexer *head, t_lexer *new)
{
	t_lexer *tmp;

	if (!head)
			return (new);
	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->prev == NULL)
		{	
			tmp->prev = head;
			head = tmp;
		}
	}
	tmp->next = new;
	new->prev = tmp;
	return (head);
}

t_tokens get_token_type(char c)
{
	if (c == '|')
		return ((t_tokens)(2));
	else if (c == '>' || c == '<')
		return ((t_tokens)(1));
	else
		return ((t_tokens)(0));
}



t_lexer	*pre_lexing(char *prompt)
{
	int			i;
	t_lexer		*new;
	t_lexer		*head = NULL;

	i = -1;
	while (prompt[++i])
	{
		new = new_node(c_to_str(prompt[i]));
		new->token = get_token_type(prompt[i]);
		new->i = i;
		head = ft_add_back_lex(head, new);
	}
	return (head);
}

