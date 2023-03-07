/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:12 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/03/04 13:15:13 by cdahlhof         ###   ########.fr       */
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

long	createGradientColor(float fraction, int r1, short g1, short b1, short r2, short g2, short b2)
{
	int red	= r1 + fraction * (r2 - r1);
	int green	= g1 + fraction * (g2 - g1);
	int blue	 = b1 + fraction * (b2 - b1);

	

	return (0 << 24 | (unsigned char)red << 16 | (unsigned char)green << 8 | (unsigned char)blue);
}

long	createMultiGradient(float fraction, int nColor, ...)
{
	--nColor;
	int		startGradient = (int)(fraction * (float)nColor);
	int		start[3] = {0, 0, 0};
	int		next[3] = {0, 0, 0};
	int		skip = 0;
	va_list	col;
	va_start(col, nColor);
	while (skip < startGradient * 3)
	{
		(void)va_arg(col, int);
		skip++;
	}
	for (int i = 0; i < 3; i++)
	{
		start[i] = va_arg(col, int);
	}
	for (int i = 0; i < 3; i++)
	{
		next[i] = va_arg(col, int);
	}
	
	float	newFraction = (fraction * (float)nColor) - (startGradient);
	return (createGradientColor(newFraction, start[0], start[1], start[2], next[0], next[1], next[2]));
}
