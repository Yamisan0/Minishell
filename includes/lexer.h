#include "minishell.h"


typedef enum
{
	WORD,
	WHITE_SPACE,
	REDIRECTION,
	PIPE
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