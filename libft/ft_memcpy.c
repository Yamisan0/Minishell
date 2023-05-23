/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:00:49 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:13:34 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
// int main(void)
// {
//     char str[] = "bonjour tout le monde";
//     char tab[] = "il ne l'a pas faitllllllllllllllll";
//     ft_memcpy(tab, str, 8 * sizeof(char));
//     printf("%s\n", tab);

//     char str2[] = "bonjour tout le monde";
//     char tab2[] = "il ne l'a pas faitlllllllllllllll";
//     memcpy(tab2, str2, 8 * sizeof(char));
//     printf("%s\n", tab2);
// }