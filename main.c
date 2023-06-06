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

int main(int ac, char **av, char **envp)
{
	char *prompt;
	char *prompt_space;
	(void)	av;
	t_lexer *test;
	(void)envp;
	global_env = set_env(envp);

	if (ac == 1)
	{
			while (42)
		{
			prompt = readline("minishell>");
				if (prompt && *prompt)
					add_history(prompt);
				prompt_space = pars_prompt(prompt);
			test = ft_lexer(prompt_space, global_env);
			ft_parser(test);
			while (test)
			{
				printf("%s   \n", test->str);
				test = test->next;
			}
			free(prompt);
		}
	}
}
