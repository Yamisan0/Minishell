#include "minishell.h"


typedef enum
{
	WORD,
	WHITE_SPACE,
	REDIRECTION,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_tokens;

typedef struct s_lexer
{
	char        *str;
	t_tokens	token;
	int         i;
	struct s_lexer  *next;
	struct s_lexer  *prev;
}                   t_lexer;

t_lexer	*pre_lexing(char *prompt);
void free_lex_list(t_lexer *head);
void    big_lexer(t_lexer *head);
char *alloc_strcat(char *s1, char *s2);
void    ft_destroy_node(t_lexer *node_to_delete);
void    double_quote_fusion(t_lexer *head);
t_lexer *ft_lexer(char *prompt);