/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:20:26 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/23 11:44:22 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **str)
{
	free (*str);
	*str = NULL;
}

void	ft_free_split(char **split)
{
	int	a;

	a = 0;
	if (!split)
		return ;
	while (split[a])
	{
		free (split[a]);
		a++;
	}
	free (split);
}

static int	nbr_word(char const *str, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == c && i != 0 && str[i - 1] != c)
			len++;
		i++;
	}
	if (i != 0 && str[i - 1] != c)
		len++;
	return (len);
}

static char	*ft_strdup_split(const char *str, char c)
{
	int			i;
	int			v;
	char		*extracted;

	i = 0;
	v = 0;
	while (str[i] && str[i] != c)
		i++;
	extracted = (char *)malloc((i + 1) * sizeof (char));
	i = 0;
	if (!extracted)
		return (0);
	while (str[i] == c && str[i])
		i++;
	while (str[i] != c && str[i])
	{
		extracted[v] = str[i];
		i++;
		v++;
	}
	extracted[v] = '\0';
	return (extracted);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split_tab;

	i = 0;
	j = 0;
	split_tab = (char **)malloc((nbr_word((char *)s, c) + 1) * sizeof(char *));
	if (!split_tab)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		split_tab[j] = ft_strdup_split(&s[i], c);
		if (!split_tab[j])
			return (NULL);
		while (s[i] != c && s[i])
			i++;
		while (s[i] && s[i] == c)
			i++;
		j++;
	}
	split_tab[nbr_word((char *)s, c)] = 0;
	return (split_tab);
}
