/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:17:03 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/18 15:18:47 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putchar(char c)
{
	int	i;

	i = 1;
	write(2, &c, 1);
	return (i);
}

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

char	*ft_itoa_printf(int n)
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

int	ft_putnbr(int n)
{
	char	*str;
	size_t	len;

	str = ft_itoa_printf(n);
	ft_putstr(str);
	len = ft_strlen(str);
	free(str);
	return (len);
}
