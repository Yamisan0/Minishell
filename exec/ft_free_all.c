#include "../includes/minishell.h"


void	ft_free_parser_lexer(t_lexer *pile)
{
	t_lexer	*tmp;

	tmp = pile;
	while (pile)
	{
		pile = pile->next;
		free(tmp->str);
		free(tmp);
		tmp = pile;
	}
}

void	ft_free_minishell_struct(t_mini *ptr, char *prompt, int indice)
{
	if (indice == 130)
		free(ptr->exec->pid);
	if (!ptr)
		return ;
	free(ptr->exec);
	if (ptr->tab_heredoc)
		ft_free_split(ptr->tab_heredoc);
	ft_free_parser_lexer(ptr->args);
	free(ptr);
	free(prompt);
	ptr = NULL;
	unlink("tmp.txt");
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		env = env->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
		tmp = env;
	}
}
void    ft_free_all(char *msg, t_exec *ptr)
{
	ft_free_split(ptr->data->tab_heredoc);
	free_env(ptr->data->env);
	ft_free_split(ptr->env);
	ptr->env = NULL;
	if (ptr->full_cmd)
		ft_free_split(ptr->full_cmd);
	free(ptr->path);
	free(ptr->pid);
	ptr->tmp = NULL;
	ft_free_parser_lexer(ptr->data->args);
	free(ptr->data);
	if (ptr)
		free(ptr);
    if (msg)
		perror(msg);
}


void	ft_free_all_exit(int indice, int code, t_env *env, char **argv)
{
	if (argv)
		ft_free_split(argv);
	free_env(env);
	if (indice == 0)
		printf("exit\n");
	exit(code);
}
