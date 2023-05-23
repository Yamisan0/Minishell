/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:32:21 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/23 11:45:11 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trim(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	debut;
	size_t	fin;
	size_t	len;
	char	*tab;

	debut = 0;
	fin = ft_strlen(str);
	while (str[debut] && is_trim(str[debut], set))
		debut++;
	while (is_trim(str[fin - 1], set) && fin > debut)
		fin--;
	len = fin - debut;
	tab = (char *)malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	len = 0;
	while (debut < fin)
	{
		tab[len] = str[debut];
		len++;
		debut++;
	}
	tab[len] = '\0';
	return (tab);
}
/* int main(void)
{
	char *str1 = "abrabraaaa";
	char *set = "a";
	printf("%s\n", ft_strtrim(str1, set));
} */