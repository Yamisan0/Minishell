/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:13:47 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 11:42:43 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (('a' <= (char)c && (char)c <= 'z') || ('A' <= (char)c
			&& (char)c <= 'Z'))
		return (1);
	return (0);
}
