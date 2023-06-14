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

void	display_env(char **array)
{
	int i = 0;

	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

// int	parser_lexer(t_lexer *head)
// {
// 	if (quote_pars(head) == 0)
// 		return (-1);
// 	if t
// }

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

int main(int ac, char **av, char **envp)
{
	char *prompt;
	char *prompt_space;
	(void)	av;
	t_lexer *test;
	t_mini	*minish;
	global_env = set_env(envp);

	if (ac == 1)
	{
			while (42)
		{
			prompt = readline("minishell>");
				if (prompt && *prompt)
					add_history(prompt);
				if (!(*prompt))
					continue;
				prompt_space = pars_prompt(prompt);
				if (prompt_space == NULL)
					continue;
			test = ft_lexer(prompt_space);
			if (quote_pars(test) == 0)
				continue;
			ft_lexer_part_2(test, global_env);
			if (ft_parser(test) == -1)
				continue;
			minish = init_mini(test);
			ft_pipex(minish->exec);
			free(prompt);
		}
	}
}
