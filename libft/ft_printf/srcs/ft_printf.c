/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:20:37 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/18 15:20:53 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	params;
	size_t	i;
	size_t	len;

	va_start(params, str);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += print_arg(str[i + 1], params);
			i++;
		}
		else
		{
			write(2, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(params);
	return (len);
}
