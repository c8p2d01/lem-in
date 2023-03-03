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

/**
 * @brief Allocate new link
 */
t_link	*ft_new_link(t_room *in, t_room *out)
{
	t_link *res = malloc(sizeof(t_link));
	if (!res)
		return (NULL);
	*res = (t_link){
		.vroom = NULL,
		.moorv = NULL,
		.flow = 0,
		.active = true
	};
	if (in)
		res->vroom = in;
	if (out)
		res->moorv = out;
	return (res);
};

/**
 * @brief Check if room a is linked to room b
 */
bool	ft_is_link(t_link *link, t_room *a, t_room *b)
{
	if (link->vroom == a && link->moorv == b)
		return (true);
	if (link->vroom == b && link->moorv == a)
		return (true);
	return (false);
}

/**
 * @brief return the flow vlaue of the link (negative if towards node)
 * @param link, t_link * ::	the link that holds the flow
 * @param mode, t_room *	::	the room the flow starts from
 * @return int			::	the flow towards the connected node
 */
int	ft_flow(t_link *link, t_room *node)
{
	if (!link || !node || !link->vroom || !link->moorv)
		return(FLOW_ERROR);
	if (link->vroom == node)
		return (link->flow);
	if (link->moorv == node)
		return (-(link->flow));
	return (FLOW_ERROR);
}

/**
 * @brief check if node a has an active link to node b
 * @param a; t_room *
 * @param b; t_room *
 */
bool	ft_has_link(t_room *a, t_room *b)
{
	int i;

	if (!a || !b)
		return (false);
	i = 0;
	while (a->links && a->links[i])
	{
		if (a->links[i]->active && ft_is_link(a->links[i], a, b))
			return (true);
		i++;
	}
	return (false);
}

t_link	*ft_active_link(t_link *link)
{
	if (!link || !link->active)
		return(NULL);
	return(link);
}

/**
 * @brief returns the node being linked to
 */
t_room	*ft_otherside(t_link *link, t_room *myside)
{
	if (!link || !myside)
		return (NULL);
	if (link->vroom == myside)
		return (link->moorv);
	if (link->moorv == myside)
		return (link->vroom);
	return (NULL);
}

/**
 * @brief Get active links size of a node
 */
size_t	ft_active_link_size(t_room *node)
{
	size_t i;
	size_t size;

	if (!node)
		return (0);
	i = 0;
	size = 0;
	while (node->links && node->links[i])
	{
		if (node->links[i]->active)
			size++;
		i++;
	}
	return (size);
}

size_t	ft_flow_link_size(t_room *node)
{
	size_t i;
	size_t size;

	if (!node)
		return (0);
	i = 0;
	size = 0;
	while (node->links && node->links[i])
	{
		if (ft_flow(node->links[i], node) != 0)
		{
			size++;
		}
		i++;
	}
	return (size);
}

void ft_setflow(t_link *link, t_room *next)
{
	if (link->flow != 0)
		link->active = false;
	if (next == link->moorv)
		link->flow--;
	else if (next == link->vroom)
		link->flow++;
}

void ft_resetflow(t_link *link, t_room *next)
{
	if (link->active == false)
		link->active = true;
	if (next == link->moorv)
		link->flow--;
	else if (next == link->vroom)
		link->flow++;
}
