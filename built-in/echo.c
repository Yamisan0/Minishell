#include "../includes/minishell.h"

int	verif_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    ft_echo(char **args)
{
	int i;

	if (args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (args[1] && (ft_strncmp(args[1], "-n", 2) == 0) && verif_n(args[1] + 2) == 1)
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
	if (ft_strcmp(args[1], "-n") != 0 && verif_n(args[1] + 2) == 0)
		printf("\n");
}