#include "../includes/minishell.h"

int	is_special_token(t_lexer *node)
{
	if (node->token == PIPE || node->token == REDIRECTION_LEFT || node->token == REDIRECTION_RIGHT)
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
char	*pars_prompt(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (str + i);
}

int		ft_nb_pipe(t_lexer *head)
{
	int		count;

	count = 0;
	while (head)
	{
		if (head->token == PIPE)
			count++;
		head = head->next;
	}
	return (count);
}

char		*ft_prompt(t_env *env)
{
	char *prompt;
	// (void)env;

	prompt = readline("minishell>");
	if (prompt && prompt[0])
		add_history(prompt);
	if (!prompt)
		return (ft_free_all_exit(0, exit_code, env), NULL);
	if (!(*prompt))
		return (free(prompt), NULL);
	prompt = pars_prompt(prompt);
	if (ft_strlen(prompt) == 0)
		return (free(prompt), NULL);
	return (prompt);
}
