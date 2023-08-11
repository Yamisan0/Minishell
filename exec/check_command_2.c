/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:02:43 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 14:02:46 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2darray(char **split)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (split[size])
		size++;
	while (i < size)
		free(split[i++]);
	free(split);
	split = NULL;
}

char	*check_slash(char *command)
{
	if (ft_strchr(command, '/') && access(command, F_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

char	*ft_norm_path(char **entire_path, char *command, int i)
{
	char	*command_path;
	char	*add_slash;

	add_slash = ft_strjoin(entire_path[i], "/");
	command_path = ft_strjoin(add_slash, command);
	free(add_slash);
	return (command_path);
}

char	*ft_path(char *command, char **envp)
{
	char	**entire_path;
	char	*command_path;
	int		i;

	i = 0;
	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (check_slash(command));
	entire_path = get_entire_path(envp);
	if (!entire_path)
		return (NULL);
	while (entire_path[i])
	{
		command_path = ft_norm_path(entire_path, command, i);
		if (access(command_path, F_OK) == 0)
		{
			ft_free_split(entire_path);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	return (ft_free_split(entire_path), NULL);
}
