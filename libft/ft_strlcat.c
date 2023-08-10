/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:24:29 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:22:18 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <bsd/bsd.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	if (!src)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	j = dst_len;
	i = 0;
	if (dst_len < (size - 1) && size > 0)
	{
		while (src[i] && dst_len + i < size - 1)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	if (dst_len >= size)
		dst_len = size;
	return (dst_len + src_len);
}
/* int main(void)
{
	char dest[30]; memset(dest, 0, 30);
	char * src = (char *)"AAAAAAAAA";
	printf("%s\n", strlcat(dest, src, 0););
	char str2[] = "mais non ce n'est pas vrai";
	char tab2[] = "impossible de le faire";
	ft_strlcat(tab2, str2, sizeof(str2));
	printf("%s\n", tab2);
} */