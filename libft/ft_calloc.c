/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:58:35 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/01 10:21:29 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmenb, size_t size)
{
	void	*ptr;

	if ((size > 0) && ((nmenb * size) / size != nmenb))
		return (NULL);
	ptr = (void *)malloc(nmenb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmenb * size);
	return (ptr);
}
/* int main(void)
{
	char *str;
	char *tab;
	
	str = ft_calloc(3, 0);
	tab = calloc(3,0);
	printf("%s\n",str);
	printf("%s", tab);
*/