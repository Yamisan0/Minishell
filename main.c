#include "includes/minishell.h"
struct s_env *global_env=NULL;

void	ft_built(char *prompt, char **envp)
{
			if (ft_strnstr(prompt, "env", 100))
				ft_print_env(set_env(envp));
			if (ft_strnstr(prompt, "pwd", 100))
				ft_pwd();
}

char	*pars_prompt(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (str + i);
}


int		ft_nb_pipe(t_lexer *head)
{
	int		count;

	count = 0;
	while (head)
	{
		if (head->token == PIPE)
			count++;
		head = head->next;
	}
	return (count);
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

char		*ft_prompt(char *prompt)
{
	char *prompt_without_spaces;

	if (prompt && *prompt)
		add_history(prompt);
	if (!(*prompt))
		return (free(prompt), NULL);
	prompt_without_spaces = pars_prompt(prompt);
	if (ft_strlen(prompt_without_spaces) == 0)
		return (free(prompt), NULL);
	return (prompt_without_spaces);	
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

int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)	av;
	t_lexer *list;
	// t_mini	*minish;
	global_env = set_env(envp);

	if (ac == 1)
	{
			while (42)
		{
			prompt = readline("minishell>");
			if (ft_prompt(prompt) == NULL)
				continue;
			list = ft_parser_lexer(ft_prompt(prompt));
			if (!list)
				continue;
/////////////////////////////////////////////////////////////////
			// minish = init_mini(test);
			// ft_pipex(minish->exec);
			// free(prompt);
		}
	}
}
