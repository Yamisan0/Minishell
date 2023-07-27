#include "includes/minishell.h"
int	exit_code = 0;

void	ft_handler_heredoc(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		exit_code = 130;
		rl_done = 1;
	}
	else if (i == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
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
}

t_mini	*init_mini(t_lexer *head, t_env *env)
{
	t_mini	*ptr;
	(void)env;
	char	**heredoc;

	ptr = ft_calloc(1, sizeof(t_mini));
	if (!ptr)
		return (NULL);
	ptr->args = head;
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, ft_handler_heredoc);
	heredoc = get_heredoc_tab(head);
	ptr->tab_heredoc = fill_heredoc_tab(heredoc, head);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	ptr->nb_pipe = ft_nb_pipe(head);
	ptr->exec = init_exec(ptr);
	ptr->exec->data = ptr;
	ptr->env = env;
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


int main(int ac, char **av, char **envp)
{
	(void)	av;
	t_lexer *list;
	char	*prompt;
	t_mini	*minish;
	t_env *minishell_env = NULL;
	minishell_env = set_env(envp);

	if (ac == 1)
	{
			while (42)
		{
			signal(SIGINT, ft_handler);
			signal(SIGQUIT, ft_handler);
			prompt = ft_prompt(minishell_env);
			if ( prompt == NULL)
				continue;
			list = ft_parser_lexer(prompt, minishell_env);
			exit_code = 0;
			if (!list)
				continue;
			ft_unset_export_no_fork(list, &minishell_env);
			minish = init_mini(list, minishell_env);
			if (exit_code == 130)
				continue;
			ft_pipex(minish->exec);
			ft_free_minishell_struct(minish, prompt);
			unlink("tmp.txt");
		}
	}
}
