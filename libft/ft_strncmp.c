/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:28:09 by imessaad          #+#    #+#             */
/*   Updated: 2022/11/22 12:27:21 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if ((!s1[i] || !s2[i]) && n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i != n)
		return (s1[i] - s2[i]);
	return (0);
}
// int main()
// {
//     char *s1 = "1234";
//     char *s2 = "1235";

//     printf("test = %d\n", ft_strncmp(s1, s2, 3));
//     printf("real = %d\n", strncmp(s1, s2, 3));
//     return (0);
// } 

// int main(void)
// {
//     strncmp('t', "", 0);
//     ft_strncmp('t', "", 0);
// }