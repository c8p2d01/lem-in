/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:23:42 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/02 15:43:27 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_putnbr_base_fd(unsigned int num, char *base, int fd)
{
	int	i;

	i = 1;
	if (num > ft_strlen(base))
		i += ft_putnbr_base_fd(num / ft_strlen(base), base, fd);
	write(fd, &(base[(num % ft_strlen(base))]), 1);
	return (i);
}
