#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[1024];
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror(""), 0);
	printf("%s\n", cwd);
	return (1);
}
