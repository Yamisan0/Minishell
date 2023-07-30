/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:19:36 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/18 15:20:26 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write (2, "(null)", 6);
		i = 6;
		return (i);
	}
	while (*str)
	{
		ft_putchar(*str++);
		i++;
	}
	return (i);
}
