/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:00:40 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:25:19 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
/* int main()
{
	char *s1 = "123";
	char *s2 = "";

	printf("real = %ld\n", strlen(s1));
	printf("real2 = %ld\n", strlen(s2));

	printf("test = %ld\n", strlen(s1));
	printf("test2 = %ld\n", strlen(s2));
} */