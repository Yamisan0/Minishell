#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_lexer
{
    char        *str;
    char        *token;
    int         i;
    struct s_lexer  *next;
    struct s_lexer  *prev;
}                   t_lexer;


#endif