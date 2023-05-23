#include "includes/minishell.h"

int main(void)
{
	char *prompt;

	while (42)
	{
		prompt = readline("minishell>");
		printf("%s\n", prompt);
		if (prompt && *prompt)
			add_history(prompt);
	}
}