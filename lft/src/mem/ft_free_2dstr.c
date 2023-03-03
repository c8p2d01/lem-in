/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2dstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:22 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/03/03 16:38:54 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/**
 * frees each of *s and then s
 * @param s [char **]
 * @return [int] 0
*/
int	free_2dstr(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i ++;
	}
	free(s);
	return (0);
}

void	unreach(void *freeMe)
{
	free(freeMe);
	freeMe = NULL;
}
