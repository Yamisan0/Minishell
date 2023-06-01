#include "includes/minishell.h"
#include "includes/lexer_parser.h"

struct s_env *global;

void	ft_built(char *prompt, char **envp)
{
			if (ft_strnstr(prompt, "env", 100))
				ft_print_env(set_env(envp));
			if (ft_strnstr(prompt, "pwd", 100))
				ft_pwd();
}

int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)	av;
	t_lexer *test;
	(void)envp;

	if (ac == 1)
	{
			while (42)
		{
			prompt = readline("minishell>");
				if (prompt && *prompt)
					add_history(prompt);
			test = ft_lexer(prompt);
			while (test)
			{
				printf("%s\n", test->str);
				test = test->next;
			}
			
			free(prompt);
		}
	}
}
