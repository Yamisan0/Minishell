#include "includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)	av;
	// t_env *ptr;
	if (ac == 1)
	{
			while (42)
		{
			prompt = readline("minishell>");
			printf("%s\n", prompt);
			if (prompt && *prompt)
				add_history(prompt);
			if (ft_strnstr(prompt, "env", 100))
				ft_print_env(set_env(envp));
		}
	}
}