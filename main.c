#include "includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	// char *prompt;
	(void)	av;
	t_env *ptr;
	if (ac == 1)
	{
		// 	while (42)
		// {
		// 	prompt = readline("minishell>");
		// 	printf("%s\n", prompt);
		// 	if (prompt && *prompt)
		// 		add_history(prompt);
			ptr = copy_env(envp);
			while (ptr->next)
			{
				printf("%s=%s\n", ptr->var, ptr->value);
				ptr = ptr->next;
			}
		// }
	}
}