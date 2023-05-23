/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:26:29 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:23:14 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <bsd/string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (src[i] && size >= 1 && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size >= 1)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
// int main(void)
// {
//     char src[] = "coucou";
//     char dest[10]; memset(dest, 'A', 10);
//     ft_strlcpy(dest, src, 0);
//     printf("%s\n", dest);
// }

// int main(void)
// {
//     char src[7] = "coucou";
//     char src2[7] = "coucou";
//     char dest[8] = "Bonjour";
//     char dest2[8] = "bonjour";
//     ft_strlcpy(dest2, src2, 0);
//     printf("ft = %s\n", dest2);
//     strlcpy(dest, src, 0);
//     printf("real = %s\n", dest);
// }