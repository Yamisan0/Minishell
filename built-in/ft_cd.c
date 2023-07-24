#include "../includes/minishell.h"

int	ft_cd(char **str)
{
	struct stat	stats;

	if (*str == NULL)
		return (chdir("/home/idris"), 1);
	if (str[1])
		return (printf("bash: cd: too many arguments\n"), 1);
	if (stat(*str, &stats))
		return (printf("bash: cd:%s\n",strerror(errno)));
	if (!S_ISDIR(stats.st_mode))
		return (printf("bash: cd: "),printf(": Not a directory\n"), 1);
	else if (chdir(*str) == -1)
		return (printf("bash: cd: %s\n",strerror(errno)));
	return (0);
}
