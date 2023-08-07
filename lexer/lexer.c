#include "../includes/minishell.h"

t_lexer *pre_lexing(char *prompt)
{
	int			i;
	t_lexer		*new;
	t_lexer		*head = NULL;
	char		*str;

	i = 0;
	while (prompt[i] && (prompt[i] == ' ' || prompt[i] == '\t'))
		i++;
	while (prompt[i])
	{
		str = c_to_str(prompt[i]);
		new = new_node(str);
		new->token = get_token_type(prompt[i]);
		head = ft_add_back_lex(head, new);
		i++;
	}
	return (head);
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

t_tokens get_token_type(char c)
{
	if (c == ' ' || c == '\t')
		return (WHITE_SPACE);
	if (c == '\'')
		return (SINGLE_QUOTE);
	if (c == '\"')
		return (DOUBLE_QUOTE);
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (REDIRECTION_RIGHT);
	if (c == '<')
		return (REDIRECTION_LEFT);
	if (c == '$')
		return (DOLLAR);
	if (ft_isalnum(c) || c == '_')
		return (ALPHA_NUM);
	if (c == '?')
		return (INTERRO);
	return (OTHER);
}

t_lexer *ft_lexer(char *prompt)
{
	t_lexer	*lexer;

	if (!prompt)
		return (NULL);
	lexer = pre_lexing(prompt);
	big_lexer(lexer);
	set_state_quotes(lexer);
	single_quote_fusion(lexer);
	dollar_lexer(lexer);
	return (lexer);
}

void	ft_lexer_part_2(t_lexer *lexer, t_env *env)
{
	ft_replace_by_litteral(lexer, env);
	ft_supp_simple_quotes(lexer);
	double_quote_fusion(lexer);
	ft_supp_double_quotes(lexer);
	ft_word(lexer);
	fusion_words(lexer);
	delete_spaces(lexer);
}
