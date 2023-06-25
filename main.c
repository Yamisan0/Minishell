#include "includes/minishell.h"
struct s_env *global_env=NULL;

void	ft_built(char *prompt, char **envp)
{
			if (ft_strnstr(prompt, "env", 100))
				ft_print_env(set_env(envp));
			if (ft_strnstr(prompt, "pwd", 100))
				ft_pwd();
}


t_mini	*init_mini(t_lexer *head)
{
	t_mini	*ptr;

	ptr = ft_calloc(1, sizeof(t_mini));
	if (!ptr)
		return (NULL);
	ptr->args = head;
	ptr->nb_pipe = ft_nb_pipe(head);
	ptr->exec = init_exec(ptr);
	ptr->exec->data = ptr;
	return (ptr);
}


t_lexer	*ft_parser_lexer(char *prompt)
{
	t_lexer	*head;

	head = ft_lexer(prompt);
	if (!head)
		return (NULL);
	if (quote_pars(head) == 0)
		return (free(prompt), ft_free_parser_lexer(head), NULL);
	ft_lexer_part_2(head, global_env);
	if (ft_parser(head) == -1)
		return (free(prompt), ft_free_parser_lexer(head), NULL);
	return (head);
}

void ft_handler(int i)
{
	if (i == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (i == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
	
}
int main(int ac, char **av, char **envp)
{
	// char *prompt;
	(void)	av;
	(void)ac;
	(void)envp;
	// t_lexer *list;
	// t_mini	*minish;
	global_env = set_env(envp);
/* 
	if (ac == 1)
	{
			while (42)
		{
			signal(SIGINT, ft_handler);
			signal(SIGQUIT, ft_handler);
			prompt = readline("minishell>");
			if (ft_prompt(prompt) == NULL)
				continue;
			list = ft_parser_lexer(ft_prompt(prompt));
			if (!list)
				continue;
/////////////////////////////////////////////////////////////////
			minish = init_mini(list);
			ft_pipex(minish->exec);
			// free(minish);
			// if (list)
				// ft_free_parser_lexer(list);
			// exit(0);	
		}
	} */
	int fd = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	char *str = ft_get_heredoc("delim");
	ft_write_in_file(str, fd);
}
