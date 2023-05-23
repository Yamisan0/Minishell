/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:09:46 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/18 15:12:01 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	len_unsigned(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	print_unsigned_int(unsigned int nbr)
{
	size_t	len;

	len = len_unsigned(nbr);
	if (nbr < 10)
	{
		ft_putchar(nbr + '0');
	}
	if (nbr > 9)
	{
		print_unsigned_int(nbr / 10);
		print_unsigned_int(nbr % 10);
	}
	return (len);
}
