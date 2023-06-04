#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H

#include "minishell.h"


typedef enum
{
	WORD,
	ALPHA_NUM,
	WHITE_SPACE,
	REDIRECTION_RIGHT,
	REDIRECTION_LEFT,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	DOLLAR,
	INTERRO,
	OTHER
}	t_tokens;

typedef enum
{
	DEFAULT,
	OPENED
}	t_state;

typedef	enum
{
	LITTERAL,
	COMPLEX
}	t_dollar;

typedef struct s_lexer
{
	char        *str;
	t_tokens	token;
	int         i;
	t_state		state;
	t_dollar	dollar;
	struct s_lexer  *next;
	struct s_lexer  *prev;
}                   t_lexer;

/* LINKED  LIST */
char *alloc_strcat(char *s1, char *s2);
void    ft_destroy_node(t_lexer *node_to_delete);
void free_lex_list(t_lexer *head);

/* LEXER */
t_lexer	*pre_lexing(char *prompt);
void    big_lexer(t_lexer *head);
t_lexer *ft_lexer(char *prompt);
void    dollar_lexer(t_lexer *head);

/* PARSER */
int	single_quote_state(t_lexer *head);
int	double_quote_validity_check(t_lexer *head);
void    set_state_quotes(t_lexer *head);
int ft_parser(t_lexer *head);

/* PARSER_ENV */
char	*ft_give_val(t_env *env, char *name);


#endif