/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:26:00 by imessaad          #+#    #+#             */
/*   Updated: 2022/12/18 16:05:52 by imessaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <inttypes.h>

int		print_arg(char chr, va_list var);
int		ft_putchar(char c);
size_t	ft_strlen(const char *str);
int		ft_putstr(char *str);
int		ft_putchar(char c);
int		ft_puthexa(unsigned int nb, char c);
int		print_percent(va_list param);
int		print_ptr(void *ptr);
char	*ft_itoa(int n);
int		ft_putnbr(int n);
int		print_unsigned_int(unsigned int nbr);
char	*ft_unsigned_itoa(unsigned int n);
int		ft_puthexa_ptr(unsigned long int nb, char c);
int		ft_printf(const char *str, ...);

#endif