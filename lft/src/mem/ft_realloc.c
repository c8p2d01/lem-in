/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:07:00 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/02 15:40:51 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_realloc(void *old, size_t ol, size_t add)
{
	char	*new;

	new = ft_calloc(ol + add, 1);
	ft_memcpy(new, old, ol);
	free(old);
	return ((void *)new);
}
