/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:16:19 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 11:45:38 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_itoa(int n)
{
	int				i;
	unsigned int	nb;

	i = 1;
	nb = n;
	if (n < 0)
	{
		i++;
		nb = n * (-1);
	}
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	nb;
	char			*str;

	str = (char *)malloc(len_itoa(n) + 1);
	if (!str)
		return (0);
	i = len_itoa(n);
	nb = n;
	if (n < 0)
	{
		nb = n * (-1);
		str[0] = '-';
	}
	str[i] = 0;
	str[i - 1] = '0';
	while (nb > 0)
	{
		i--;
		str[i] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}
// int main(void)
// {
//     char *str = ft_itoa(INT_MIN);
//     printf("%s\n", str);
// }