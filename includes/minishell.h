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

typedef struct s_env
{
	char			*var;
	char			*value;
	int				index;
	struct s_env	*next;
}					t_env;

typedef struct s_lexer
{
	char        *str;
	char        *token;
	int         i;
	struct s_lexer  *next;
	struct s_lexer  *prev;
}                   t_lexer;

/* ENV */
t_env	*set_env(char **envp);
int		ft_print_env(t_env *env);
t_env	*add_to_list(t_env *head, t_env *new);
t_env   *create_node(char *str_to_cpy);

/* EXPORT */
void	export(char *var, char *value, t_env *env);


int		ft_pwd(void);
#endif