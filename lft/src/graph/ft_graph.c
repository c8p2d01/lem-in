/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:08:04 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/14 15:25:46 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_room.h"

/**
 * @brief Allocate a new node
 */
t_room	*ft_g_new_node(char *name)
{
	t_room *res = ft_calloc(sizeof(t_room), 1);
	if (res)
	{
		res->links = NULL;
		res->name = name;
		res->x = 0;
		res->y = 0;
		res->lvl = -1
	}
	return (res);
}
