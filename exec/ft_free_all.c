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

void	ft_free_minishell_struct(t_mini *ptr, char *prompt)
{
	if (!ptr)
		return ;
	if (ptr->exec)
		free(ptr->exec);
	if (ptr->tab_heredoc)
		ft_free_split(ptr->tab_heredoc);
	ft_free_parser_lexer(ptr->args);
	free(ptr);
	free(prompt);
	ptr = NULL;
}

void    ft_free_all(char *msg, t_exec *ptr)
{
	if (ptr->full_cmd)
		ft_free_split(ptr->full_cmd);
	if (ptr->full_cmd)
		ft_free_split(ptr->env);
	free(ptr->path);
	ptr->tmp = NULL;
	// if (ptr->data->exec)
	// 	free(ptr->data->exec);
	ft_free_parser_lexer(ptr->data->args);
	if (ptr)
		free(ptr);
    if (msg)
		perror(msg);
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

void	ft_free_all_exit(t_env *env)
{
	free_env(env);
	printf("\nexit\n");
	exit(0);
}