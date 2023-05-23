/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:15:46 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:05:49 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}
// int main(void)
// {
//     char str[23] = "bonjour tout le monde!";
//     printf("%s\n", str);
//     ft_memset(str, 'u', 7 * sizeof(char));
//     // memset(str, 'u', 7 * sizeof(char));
//     printf("%s\n", str);
//
//}