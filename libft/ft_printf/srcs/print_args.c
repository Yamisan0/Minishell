/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:29:06 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/18 15:55:00 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	print_arg(const char chr, va_list param)
{
	if (chr == 'c')
		return (ft_putchar((char) va_arg(param, int)));
	else if (chr == 's')
		return (ft_putstr(va_arg(param, char *)));
	else if (chr == 'p')
		return (print_ptr(va_arg(param, void *)));
	else if (chr == 'd' || chr == 'i')
		return (ft_putnbr(va_arg(param, int)));
	else if (chr == 'u')
		return (print_unsigned_int(va_arg(param, unsigned int)));
	else if (chr == 'x')
		return (ft_puthexa(va_arg(param, int), 'x'));
	else if (chr == 'X')
		return (ft_puthexa(va_arg(param, int), 'X'));
	else if (chr == '%')
	{
		ft_putchar('%');
		return (1);
	}
	else
		return (0);
}
