#include "../includes/minishell.h"

int	ft_cd(char **str)
{
	struct stat	stats;

	if (*str == NULL)
		return (chdir("/home/idris"), 1);
	if (str[1])
		return (ft_printf("minishell: cd: too many arguments\n"), exit_code = 1, 1);
	if (stat(*str, &stats))
		return (ft_printf("minishell: cd: %s: %s\n",str[0] , strerror(errno)), exit_code = 1);
	if (!S_ISDIR(stats.st_mode))
		return (ft_printf("minishell: cd: %s: Not a directory\n", str[0]), exit_code = 1, 1);
	else if (chdir(*str) == -1)
		return (ft_printf("minishell: cd: %s: %s\n",str[0] , strerror(errno)));
	return (0);
}
