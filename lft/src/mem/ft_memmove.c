/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:42:32 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/02 20:40:41 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*pdst;
	unsigned char	*psrc;

	if (!src && !dst)
		return (dst);
	psrc = (unsigned char *) src;
	pdst = (unsigned char *) dst;
	if (dst < src)
		dst = ft_memcpy(dst, src, n);
	else
	{
		i = 0;
		while (n > i)
		{
			pdst[n - i - 1] = psrc[n - i - 1];
			i++;
		}
	}
	return ((void *) dst);
}
