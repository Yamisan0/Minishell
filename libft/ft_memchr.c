/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:06:44 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:04:34 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == ((unsigned char)c))
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (0);
}
// int main(void)
// {
//     char str[] = "Bonjour";
//     void *s = ft_memchr(str, 0, 0);
//     printf("%p\n", s);
//     s = memchr(str, 0, 0);
//     printf("%p\n", s);
// }