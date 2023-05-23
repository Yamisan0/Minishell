/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:21:00 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/18 16:42:07 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_len_hexa(size_t nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
	{
		len = 1;
		return (len);
	}
	while (nbr != 0)
	{
		nbr = nbr / 16;
		len++;
	}
	return (len);
}

int	ft_puthexa(unsigned int nb, char c)
{
	char	*base;
	size_t	len;

	len = ft_len_hexa(nb);
	if (c == 'X')
		base = "0123456789ABCDEF";
	else if (c == 'x')
		base = "0123456789abcdef";
	if (nb < 16)
	{
		ft_putchar(base[nb]);
	}
	if (nb >= 16)
	{
		ft_puthexa(nb / 16, c);
		ft_puthexa(nb % 16, c);
	}
	return (len);
}

int	ft_puthexa_ptr(unsigned long int nb, char c)
{
	char	*base;
	size_t	len;

	len = ft_len_hexa(nb);
	if (c == 'X')
		base = "0123456789ABCDEF";
	else if (c == 'x')
		base = "0123456789abcdef";
	if (nb < 16)
	{
		ft_putchar(base[nb]);
	}
	if (nb >= 16)
	{
		ft_puthexa_ptr(nb / 16, c);
		ft_puthexa_ptr(nb % 16, c);
	}
	return (len);
}
