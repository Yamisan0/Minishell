#include "includes/minishell.h"
#include "includes/lexer_parser.h"

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

int main(int ac, char **av, char **envp)
{
	char *prompt;
	char *prompt_space;
	(void)	av;
	t_lexer *test;
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
			char **envi = create_envp(global_env);
			display_env(envi);
			free(prompt);
		}
	}
}
