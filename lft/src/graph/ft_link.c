/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:08:04 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/14 15:25:46 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

t_link	*ft_new_link(t_room *in, t_room *out)
{
	t_link *res = malloc(sizeof(t_link));
	if (res)
	{
		res->vroom = NULL;
		if (in)
			res->vroom = in;
		res->moorv = NULL;
		if (out)
			res->moorv = out;
		res->flow = 0;
		res->r_flow = 0;
		res->active = true;
	}
	return (res);
};

bool	ft_is_link(t_link *link, t_room *a, t_room *b)
{
	if (link->vroom == a && link->moorv == b)
		return (true);
	if (link->vroom == b && link->moorv == a)
		return (true);
	return (false);
	
}
