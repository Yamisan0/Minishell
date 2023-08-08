/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:56:35 by imessaad          #+#    #+#             */
/*   Updated: 2023/02/27 10:47:27 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t	ft_atoi(const char *nptr)
{
	int			i;
	int64_t		nbr;
	int			signe;
	int			tmp;

	i = 0;
	nbr = 0;
	signe = 1;
	if (!nptr)
		return (0);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		signe = -1;
	if (signe == -1 || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		tmp = nbr;
		nbr = (nbr * 10) + (nptr[i++] - '0');
		if (tmp > nbr)
			return (-1625893402);
	}
	return (nbr * signe);
}
