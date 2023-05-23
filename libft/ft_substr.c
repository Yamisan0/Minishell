/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:33:00 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/23 11:33:38 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	taille;

	taille = ft_strlen(s);
	if (start > taille)
		return (ft_strdup(""));
	if (len > taille - start)
		len = taille - start;
	i = 0;
	str = (char *)malloc((len + 1) * (sizeof(char)));
	if (!str)
		return (NULL);
	while (i < len && s[i + start])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* int main(void)
{
    char *str = "Bonjour";
    char *b = ft_substr(str, 1, 5);
    printf("%s", b);
} */