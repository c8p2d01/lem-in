/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:39 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/02 15:14:54 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isnumeric(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if ((!ft_isdigit(num[i]) && (i != 0)) || \
		(!ft_isdigit(num[i]) && num[i] != '+' && num[i] != '-' && i == 0))
			return (0);
		i++;
	}
	return (1);
}
