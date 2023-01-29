/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:47:42 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/23 15:18:19 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	prointer(unsigned int p)
{
	write(1, "0x", 2);
	return (ft_putnbr_base_fd(p, \
		"0123456789abcdef", 1) + 2);
}

int	out_spread(char n, va_list ap)
{
	char	*s;

	if (n == 'c')
	{
		n = (char)va_arg(ap, int);
		return (write(1, &n, 1));
	}
	else if (n == 'x')
		return (ft_putnbr_base_fd(va_arg(ap, int), "0123456789abcdef", 1));
	else if (n == 'i' || n == 'd')
		return (ft_putnbr_base_fd(va_arg(ap, int), "0123456789", 1));
	else if (n == 'p')
		return (prointer((unsigned long)va_arg(ap, void *)));
	else if (n == 's')
	{
		s = va_arg(ap, char *);
		return (write(1, s, ft_strlen(s)));
	}
	else if (n == 'u')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), "0123456789", 1));
	else if (n == '%')
		return (write(1, "%", 1));
	else if (n == 'X')
		return (ft_putnbr_base_fd(va_arg(ap, int), "0123456789ABCDEF", 1));
	return (-2147483648);
}

// 0 -> normal
// 1 -> char
// 2 -> hexa
// 3 -> integer & decimal
// 4 -> pointer
// 5 -> string
// 6 -> unsigned integer
// 7 -> %
// 8 -> Big Hexa
int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		total;

	i = -1;
	total = 0;
	va_start(ap, str);
	while (str[++i])
	{
		if (str[i] != '%')
		{
			total += write(1, str + i, 1);
			continue ;
		}
		else
		{
			i++;
			total += out_spread(str[i], ap);
		}
	}
	return (total);
}
