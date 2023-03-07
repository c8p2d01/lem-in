/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:47:42 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/03/04 10:36:35 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	print_pointer(int fd, unsigned int p)
{
	write(1, "0x", 2);
	return (ft_putnbr_base_fd(p, \
		"0123456789abcdef", fd) + 2);
}

int	function_delegation_fd(int fd, char n, va_list ap)
{
	char	*s;

	if (n == 'c')
	{
		n = (char)va_arg(ap, int);
		return (write(fd, &n, 1));
	}
	else if (n == 'x')
		return (ft_putnbr_base_fd(va_arg(ap, int), "0123456789abcdef", fd));
	else if (n == 'i' || n == 'd')
		return (ft_putnbr_base_fd(va_arg(ap, int), "0123456789", fd));
	else if (n == 'p')
		return (print_pointer(fd, (unsigned long)va_arg(ap, void *)));
	else if (n == 's')
	{
		s = va_arg(ap, char *);
		return (write(fd, s, ft_strlen(s)));
	}
	else if (n == 'u')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), "0123456789", fd));
	else if (n == '%')
		return (write(fd, "%", 1));
	else if (n == 'X')
		return (ft_putnbr_base_fd(va_arg(ap, int), "0123456789ABCDEF", fd));
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
int	ft_printf_fd(int fd, const char *str, ...)
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
			total += write(fd, str + i, 1);
			continue ;
		}
		else
		{
			i++;
			total += function_delegation_fd(fd, str[i], ap);
		}
	}
	return (total);
}
