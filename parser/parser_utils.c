/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:01:16 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 17:31:41 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_token(t_lexer *node)
{
	if (node->token == PIPE || node->token == REDIRECTION_LEFT
		|| node->token == REDIRECTION_RIGHT)
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

int	ft_nb_pipe(t_lexer *head)
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

char	*ft_prompt(t_env *env)
{
	char	*prompt;

	prompt = readline("minishell>");
	if (prompt && prompt[0])
		add_history(prompt);
	if (!prompt)
		return (ft_free_all_exit(0, g_ecode, env, NULL), NULL);
	if (!(*prompt))
		return (free(prompt), NULL);
	if (pars_prompt(prompt) == NULL)
		return (free(prompt), NULL);
	return (prompt);
}
