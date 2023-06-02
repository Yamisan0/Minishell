#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H

#include "minishell.h"


typedef enum
{
	ALPHA_NUM,
	WHITE_SPACE,
	REDIRECTION,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	DOLLAR,
	OTHER
}	t_tokens;

typedef enum
{
	SIMPLE,
	COMPLEXE
}	t_dollar;

typedef struct s_lexer
{
	char        *str;
	t_tokens	token;
	int         i;
	t_dollar	dol;
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
int	double_quote_state(t_lexer *head);
int	single_quote_state(t_lexer *head);
int ft_parser(t_lexer *head);
#endif