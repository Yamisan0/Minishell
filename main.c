#include "includes/minishell.h"
#include "includes/lexer.h"

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
	// t_env *ptr;
	(void)envp;
	if (ac == 1)
	{
			while (42)
		{
			prompt = readline("minishell>");
				// if (prompt && *prompt)
			test = pre_lexing(prompt);
			while (test)
			{
				printf("%s     token : %d\n", test->str, test->token);
				test = test->next;
			}
			// add_history(prompt);
			free(prompt);
			// test = NULL;
		}
	}
}