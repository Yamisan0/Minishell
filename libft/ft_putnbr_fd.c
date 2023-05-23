/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:17:53 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:12:27 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	long int	div;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd(45, fd);
		nb *= -1;
	}
	div = nb / 10;
	nb = nb % 10;
	if (div)
		ft_putnbr_fd(div, fd);
	ft_putchar_fd(nb + 48, fd);
}
