/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:47:42 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/02 20:25:19 by cdahlhof         ###   ########.fr       */
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
		n = va_arg(ap, int);
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

int	indidentify(const char *str)
{
	if (str[0] == '%')
	{
		if (str[1] == 'c')
			return (1);
		else if (str[1] == 'x')
			return (2);
		else if (str[1] == 'i' || str[1] == 'd')
			return (3);
		else if (str[1] == 'p')
			return (4);
		else if (str[1] == 's')
			return (5);
		else if (str[1] == 'u')
			return (6);
		else if (str[1] == '%')
			return (7);
		else if (str[1] == 'X')
			return (8);
	}
	return (0);
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
	int		n;
	int		total;

	i = -1;
	n = 0;
	total = 0;
	va_start(ap, str);
	while (str[++i] && n >= 0)
	{
		n = indidentify(&str[i]);
		if (str[i] != '%')
		{
			write(1, str + i, 1);
			total++;
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
