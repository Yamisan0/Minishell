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
#include <fcntl.h>

extern struct s_env *global_env;


typedef struct s_env
{
	char			*var;
	char			*value;
	int				index;
	struct s_env	*next;
}					t_env;


typedef enum
{
	WORD,
	IN,
	OUT,
	DIN,
	DOUT,
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

typedef struct s_minishell
{
	t_lexer *args;
	int		nb_pipe;
	int		nb_dout;
	int		nb_out;
	int		nb_in;
}					t_mini;


/* TOKEN TYPE */
t_tokens get_token_type(char c);
int	is_special_token(t_lexer *node);

/* LINKED  LIST */
char *alloc_strcat(char *s1, char *s2);
void    ft_destroy_node(t_lexer *node_to_delete);
void free_lex_list(t_lexer *head);

/* LEXER */
t_lexer	*pre_lexing(char *prompt);
void    big_lexer(t_lexer *head);
t_lexer *ft_lexer(char *prompt);
void	ft_lexer_part_2(t_lexer *lexer, t_env *env);
void    dollar_lexer(t_lexer *head);
void	fusion_reste(t_lexer *head);
void	delete_spaces(t_lexer *head);
void	ft_fusion_double_quotes(t_lexer *head);

/* PARSER */
int	single_quote_state(t_lexer *head);
int	double_quote_validity_check(t_lexer *head);
void    set_state_quotes(t_lexer *head);
int	quote_pars(t_lexer *head);
void	set_redirection_type(t_lexer *head);
int    ft_check_in_redirect(t_lexer *head);
int ft_parser(t_lexer *head);

/* PARSER UTILS */
int	ft_strcmp(char *s1, char *s2);

/* PARSER_ENV */
char	*ft_give_val(t_env *env, char *name);
void	ft_replace_by_litteral(t_lexer *head, t_env *env);


/* GET ARG */
char *ft_argv(t_lexer *head, int i);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* -------------------------------------------------EXECUTION----------------------------------------------- */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ENV */
t_env	*set_env(char **envp);
int		ft_print_env(t_env *env);
t_env	*add_to_list(t_env *head, t_env *new_node);
t_env   *create_node(char *str_to_cpy);

/* EXPORT */
void	ft_export(char *var, char *value, t_env *env);


int		ft_pwd(void);





/* EXEC */
char **create_envp(t_env *env);
#endif