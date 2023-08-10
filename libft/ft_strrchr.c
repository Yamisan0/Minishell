/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:37:40 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:29:38 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == ((char)c))
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
/* int main(void)
{
	
	printf("%p\n", ft_strrchr("salut", 'l'));
	printf("%p\n", strrchr("salut", 'l'));
} */
