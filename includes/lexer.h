#include "minishell.h"


typedef enum
{
	WORD,
	REDIRECTION,
	PIPE
}	t_tokens;

typedef struct s_lexer
{
	char        *str;
	t_tokens	token;
	int         i;
	struct s_lexer  *next;
	// struct s_lexer  *prev;
}                   t_lexer;

t_lexer	*pre_lexing(char *prompt);
void    ft_free_parsed_prompt(t_lexer *list);