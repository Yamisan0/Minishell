/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:22:02 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/18 16:39:02 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	print_ptr(void *ptr)
{
	size_t	len;

	len = 0;
	if (ptr == NULL || ptr == 0)
	{
		write(1, "(nil)", 5);
		len = 5;
		return (len);
	}
	else
	{
		write(1, "0x", 2);
		len = 2 + ft_puthexa_ptr((uintptr_t)ptr, 'x');
	}
	return (len);
}
