/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:14:50 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:16:24 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	if (dest > src)
	{
		i = (int)n - 1;
		while ((int)i >= 0)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dest);
}
/* int main(void)
{
	char str[] = "pas ouf les gens";
	char tab[] = "Bonjour toutgggggggggggggggg";
	memmove(tab, str, 6);
	printf("%s\n", tab);
	char str2[] = "pas ouf les gens";
	char tab2[] = "Bonjour toutgggggggggggggggg";
	ft_memmove(tab2, str2, 6);
	printf("%s\n", tab2);
} */