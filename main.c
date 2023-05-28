#include "includes/minishell.h"

void	ft_built(char *prompt, char **envp)
{
	if (prompt && *prompt)
				add_history(prompt);
			if (ft_strnstr(prompt, "env", 100))
				ft_print_env(set_env(envp));
			if (ft_strnstr(prompt, "pwd", 100))
				ft_pwd();
			
}

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
			ft_built(prompt, envp);
		}
	}
}