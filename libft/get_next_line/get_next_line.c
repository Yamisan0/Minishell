/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:09:53 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/14 15:40:33 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_reset(char *str1, char *str2)
{
	char	*join;

	join = ft_strjoin(str1, str2);
	free(str1);
	return (join);
}

char	*create_tab(int fd, char *tab)
{	
	char	*buffer;
	int		b_read;

	b_read = 1;
	if (!tab)
		tab = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (b_read > 0 && (!(ft_strrchr(buffer, '\n'))))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[b_read] = '\0';
		tab = ft_reset(tab, buffer);
	}
	free(buffer);
	return (tab);
}

char	*get_line(char *tab)
{
	size_t	i;
	char	*copy;
	size_t	pos;

	pos = 0;
	while (tab[pos] && tab[pos] != '\n')
		pos++;
	copy = ft_calloc((pos + 2), sizeof(char));
	i = 0;
	while (tab[i] != '\n' && tab[i])
	{
		copy[i] = tab[i];
		i++;
	}
	if (tab[i] && tab[i] == '\n')
		copy[i] = '\n';
	return (copy);
}

char	*get_next(char *tab)
{
	size_t	i;
	char	*new_tab;
	size_t	j;

	i = 0;
	j = 0;
	while (tab[i] != '\n' && tab[i])
		i++;
	if (tab[i] == '\0')
	{
		free(tab);
		return (NULL);
	}
	new_tab = ft_calloc((ft_strlen(tab) - i + 1), sizeof(char));
	i = i + 1;
	while (tab[i])
	{
		new_tab[j] = tab[i];
		j++;
		i++;
	}
	free(tab);
	return (new_tab);
}

char	*get_next_line(int fd)
{
	static char		*str = NULL;
	char			*line;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	str = create_tab(fd, str);
	if (!str)
		return (NULL);
	else if (str[0] == '\0')
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	line = get_line(str);
	if (!line)
		return (NULL);
	str = get_next(str);
	return (line);
}
