/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:12 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/23 15:07:53 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// color codes in rainbow sequence (len=30) for \e[38;5;%im{...}
int	colorflow(int i)
{
	int m = i % 30;
	if (m < 6)
		return(21 + (m * 36));
	if (m < 11)
		return(200 - (m - 6));
	if (m < 16)
		return(202 + ((m - 11) * 6));
	if (m < 21)
		return(190 - ((m - 16) * 36));
	if (m < 26)
		return(47 + (m - 21));
	if (m < 31)
		return(45 - ((m - 26) * 6));
	return (0);
}