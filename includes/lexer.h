#include "minishell.h"


typedef enum
{
	WORD,			//0
	WHITE_SPACE,	//1
	REDIRECTION,	//2
	PIPE,			//3
	SINGLE_QUOTE,	//4
	DOUBLE_QUOTE	//5
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