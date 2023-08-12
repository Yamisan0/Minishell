/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:19:51 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/12 16:07:28 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

extern int			g_ecode;

typedef struct s_env
{
	char			*var;
	char			*value;
	int				index;
	struct s_env	*next;
}					t_env;

typedef enum s_tokens
{
	WORD,
	HEREDOC,
	DELIMITER,
	IN,
	INFILE,
	OUT,
	OUTFILE,
	DIN,
	DOUT,
	COMMAND,
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
}			t_tokens;

typedef enum s_state
{
	DEFAULT,
	OPENED
}			t_state;

typedef enum s_dollar
{
	LITTERAL,
	COMPLEX
}			t_dollar;

typedef enum s_fds
{
	NOT,
	VISITED
}	t_fds;

typedef struct s_lexer
{
	char			*str;
	int				i;
	int				index_heredoc;
	int				index_pipe;
	t_tokens		token;
	t_state			state;
	t_dollar		dollar;
	t_fds			redirection;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_exe
{
	pid_t				*pid;
	int					fd[2];
	pid_t				prev;
	t_lexer				*tmp;
	char				**full_cmd;
	char				*cmd;
	char				*path;
	char				**env;
	char				**path_split;
	t_lexer				*tmp_red;
	t_tokens			redirect;
	struct s_minishell	*data;
}				t_exec;

typedef struct s_minishell
{
	t_lexer			*args;
	int				nb_pipe;
	char			**tab_heredoc;
	int				code_error;
	int				nb_here;
	struct s_env	*env;
	struct s_exe	*exec;
}					t_mini;

// TOKEN TYPE //

t_tokens	get_token_type(char c);
int			is_special_token(t_lexer *node);

// LINKED  LIST //

char		*alloc_strcat(char *s1, char *s2);
void		ft_destroy_node(t_lexer *node_to_delete);

// LEXER_UTILS //
char		*c_to_str(char c);
t_lexer		*new_node(char *str);
t_lexer		*ft_add_back_lex(t_lexer *head, t_lexer *new);
void		ft_set_index_pipe(t_lexer *lexer);
int			next_space(char *str);

// LEXER //
t_lexer		*pre_lexing(char *prompt);
void		fusion_words(t_lexer *head);
void		ft_word(t_lexer *head);
void		check_after_expand(t_lexer *lexer);
void		big_lexer(t_lexer *head);
t_lexer		*ft_parser_lexer(char *prompt, t_env *env);
void		single_quote_fusion(t_lexer *head);
void		ft_supp_simple_quotes(t_lexer *head);
void		ft_supp_double_quotes(t_lexer *head);
void		double_quote_fusion(t_lexer *head);
t_lexer		*ft_lexer(char *prompt);
int			ft_lexer_part_2(t_lexer *lexer, t_env *env);
void		dollar_lexer(t_lexer *head);
void		fusion_reste(t_lexer *head);
int			ft_check_debut_null(t_lexer *lexer);
void		delete_spaces(t_lexer *head);
void		ft_fusion_double_quotes(t_lexer *head);

// PROMPT //
char		*ft_prompt(t_env *env);
// PARSER //
int			single_quote_state(t_lexer *head);
int			double_quote_validity_check(t_lexer *head);
void		set_state_quotes(t_lexer *head);
int			quote_pars(t_lexer *head);
void		set_redirection_type(t_lexer *head);
void		ft_set_infile_outfile(t_lexer *head);
int			ft_parser(t_lexer *head);

// PARSER UTILS //
int			ft_strcmp(char *s1, char *s2);

// PARSER_ENV //
char		*ft_give_val(t_env *env, char *name);
void		ft_replace_by_litteral(t_lexer *head, t_env *env);

//-------------------EXECUTION--------------------//

int			ft_nb_pipe(t_lexer *head);

// ENV //
t_env		*set_env(char **envp);
int			ft_print_env(t_env *env);
t_env		*add_to_list(t_env *head, t_env *new_node);
void		cpy_tab(char *str, t_env *node);
t_env		*create_node(char *str_to_cpy);
void		set_index_env(t_env	*env);

// EXPORT //
void		ft_export(t_env **env, char **argv);
int			ft_pwd(void);

// UTILS //
void		display_env(char **array);
int			count_pipe(t_lexer *head);
void		ft_write_error(char *s1, char *s2, char *s3);

// REDIRECTION //
int			open_files(int indice, char *path, char *name);
int			ft_redir(t_exec *ptr);
int			ft_open_n_dup(int indice, t_lexer *head, t_exec *ptr);
int			ft_open(t_lexer *head, t_exec *ptr);
// EXEC //
char		**ft_command(t_lexer *head);
int			set_exec(t_exec *ptr, int i, t_env *env);
int			dup_close_fd_pipe(t_exec *ptr, int i);
char		**get_entire_path(char **envp);
char		*ft_path(char *command, char **envp);
char		**create_envp(t_env *env);
t_exec		*init_exec(t_mini *ptr);
t_lexer		*ret_next_pipe(t_lexer *head, int i);
int			count_in(t_lexer *head);
t_lexer		*ft_next_redirection(t_lexer *head, t_exec *ptr);
int			ft_pipex(t_exec *ptr);
void		wait_all_pids(t_exec *args);
void		ft_cpy_std(t_exec *ptr);
void		dupclosestd(t_exec *ptr);

// HEREDOC //
void		ft_write_in_file(char *str_doc, int fd, t_env *env);
char		*ft_get_heredoc(char *delimiter);
char		**get_heredoc_tab(t_lexer *head);
char		**fill_heredoc_tab(char **tab, t_lexer *head);

// FREE //
void		ft_free_parser_lexer(t_lexer *head);
void		ft_free_minishell_struct(t_mini *ptr, char *prompt, int indice);
void		ft_free_all(char *msg, t_exec *ptr);
void		ft_free_all_exit(int indice, int code, t_env *env, char **argv);
void		free_env(t_env *env);

// BUILT-IN //
void		ft_echo(char **args);
int			ft_cd(char **str, t_env **env);
int			ft_check_builtin(char **argv);
void		ft_unset_export_no_fork(t_lexer **args, t_env **env);
int			ft_exit_parsing(char **argv);
void		ft_exit(char **argv, t_env *env);
char		*return_equal(char *arg);
int			export_parsing(char **argv);
t_env		*ft_check_exist(t_env *env, char *arg);
void		ft_export_sans_arg(t_env *env);
int			ft_built_in(char **argv, t_env *env, t_lexer *args);

// SIGNALS //
void		ft_handler_exec(int i);
void		ft_handler(int i);
void		ft_handler_heredoc(int i);

#endif