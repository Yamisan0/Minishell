#include "../includes/minishell.h"

void    ft_echo(char **args)
{
	int i;

	if (args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
		i = 2;
	else
		i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(args[1], "-n") != 0)
		printf("\n");
}