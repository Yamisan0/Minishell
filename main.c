#include "includes/minishell.h"
int	exit_code = 0;

t_mini	*init_mini(t_lexer *head, t_env *env)
{
	t_mini	*ptr;
	char	**heredoc;

	ptr = ft_calloc(1, sizeof(t_mini));
	if (!ptr)
		return (NULL);
	ptr->args = head;
	ptr->nb_pipe = ft_nb_pipe(head);
	ptr->exec = init_exec(ptr);
	ptr->exec->data = ptr;
	ptr->env = env;
	heredoc = get_heredoc_tab(head);
	ptr->tab_heredoc = fill_heredoc_tab(heredoc, head);
	return (ptr);
}


t_lexer	*ft_parser_lexer(char *prompt, t_env *env)
{
	t_lexer	*head;

	head = ft_lexer(prompt);
	if (!head)
		return (NULL);
	if (quote_pars(head) == 0)
		return (free(prompt), ft_free_parser_lexer(head), NULL);
	ft_lexer_part_2(head, env);
	if (ft_parser(head) == -1)
		return (free(prompt), ft_free_parser_lexer(head), NULL);
	return (head);
}

void ft_handler(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (i == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
		// ft_free_all_exit();
}
int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)	av;
	(void)ac;
	t_lexer *list;
	t_mini	*minish;
	t_env *minishell_env = set_env(envp);

	if (ac == 1)
	{
			signal(SIGINT, ft_handler);
			signal(SIGQUIT, ft_handler);
			while (42)
		{
			prompt = readline("minishell>");
			if (ft_prompt(prompt) == NULL)
				continue;
			list = ft_parser_lexer(ft_prompt(prompt), minishell_env);
			exit_code = 0;
			if (!list)
				continue;
			minish = init_mini(list, minishell_env);
			ft_pipex(minish->exec);
			if (minish->tab_heredoc)
				free(minish->tab_heredoc);
			free(minish);
			unlink("tmp.txt");
		}
	}
	
}
