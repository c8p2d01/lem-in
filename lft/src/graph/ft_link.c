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

/** 
 * @brief return the flow vlaue of the link
 * @param link, t_link * ::	the link that holds the flows
 * @param r, t_room *	::	the room the flow starts from
 * @return int			::	the flow towards the connected node
 */
int	ft_flow(t_link *link, t_room *r)
{
	if (link->vroom == r)
		return(link->flow);
	if (link->moorv == r)
		return(link->r_flow);
	return (FLOW_ERROR);
}

/** 
 * @brief return the rflow vlaue of the link
 * @param link, t_link * ::	the link that holds the flows
 * @param r, t_room *	::	the room the flow leads to
 * @return int			::	the flow coming from the connected node
 */
int	ft_r_flow(t_link *link, t_room *r)
{
	if (link->vroom == r)
		return(link->r_flow);
	if (link->moorv == r)
		return(link->flow);
	return (FLOW_ERROR);
}

/**
 * @brief check if node a has a link to node b
 * @param a; t_room *
 * @param b; t_room *
 */
bool	ft_has_link(t_room *a, t_room *b)
{
	int i = 0;

	if (!a || !b)
		return(false);
	while (a->links && a->links[i])
	{
		if (ft_is_link(a->links[i], a, b))
			return(true);
		i++;
	}
	return (false);
}

t_link	*ft_active_link(t_link *link)
{
	if (!link->active)
		return(NULL);
	return(link);
}
