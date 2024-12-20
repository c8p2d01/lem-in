/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemins.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:23:47 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/12/18 11:52:52 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

// t_link	*ft_active_link(t_link *link)
// {
// 	if (!link || !link->active)
// 		return(NULL);
// 	return(link);
// }

// /**
//  * @brief Get active links size of a node
//  */
// size_t	ft_active_link_size(t_graph *node)
// {
// 	size_t i;
// 	size_t size;

// 	if (!node)
// 		return (0);
// 	i = 0;
// 	size = 0;
// 	while (node->links && node->links[i])
// 	{
// 		if (node->links[i]->active)
// 			size++;
// 		i++;
// 	}
// 	return (size);
// }

// size_t	ft_capacity_link_size(t_graph *node)
// {
// 	size_t i;
// 	size_t size;

// 	if (!node)
// 		return (0);
// 	i = 0;
// 	size = 0;
// 	while (node->links && node->links[i])
// 	{
// 		if (ft_capacity(node->links[i], node) != 0)
// 		{
// 			size++;
// 		}
// 		i++;
// 	}
// 	return (size);
// }

// void	ft_setcapacity(t_link *link, t_graph *next)
// {
// 	if (link->capacity != 0)
// 		link->active = false;
// 	if (next == link->to)
// 		link->capacity--;
// 	else if (next == link->from)
// 		link->capacity++;
// }

// void	ft_resetcapacity(t_link *link, t_graph *next)
// {
// 	if (link->active == false)
// 		link->active = true;
// 	if (next == link->to)
// 		link->capacity--;
// 	else if (next == link->from)
// 		link->capacity++;
// }
