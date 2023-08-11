#include "../includes/minishell.h"

void	change_value_pwd(t_env **env)
{
	t_env	*tmp;
	char	current_directory[1000];

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PWD") == 0)
		{
			if (getcwd(current_directory, sizeof(current_directory)))
			{
				free(tmp->value);
				tmp->value = ft_strdup(current_directory);
			}
			return ;
		}
		tmp = tmp->next;
	}
}

int	ft_cd(char **str, t_env **env)
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
	if (env)
		change_value_pwd(env);
	return (0);
}
