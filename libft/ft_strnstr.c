/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:29:25 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:29:22 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0] || !little)
		return ((char *)big);
	if (!big || !little)
		return (0);
	while (i < n && big[i])
	{
		j = 0;
		while (little[j] && big[i + j] && i + j < n)
		{
			if (little[j] != big[i + j])
				break ;
			j++;
			if (!little[j])
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
// int main(void)
// {
//     char big[] = "Bonjour tout le monde!";
//     char little[] = "tout";
//     printf("%p\n", ft_strnstr(big, little, 12 * sizeof(char)));
// }