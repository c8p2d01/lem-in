/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemins2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:23:59 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/12/18 13:17:34 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

// void	dry(t_graph **all)
// {
// 	for (int i = 0; all[i]; i++)
// 	{
// 		all[i]->capacity = false;
// 	}
// }

///**
// * @brief return the capacity vlaue of the link (negative if towards node)
// * @param link, t_link * ::	the link that holds the capacity
// * @param mode, t_graph *	::	the graph the capacity starts from
// * @return int			::	the capacity towards the connected node
// */
//int	ft_g_capacity(t_link *link, t_graph *node)
//{
//	if (!link || !node || !link->from || !link->to)
//		return (FLOW_ERROR);
//	if (link->from == node)
//		return (link->capacity);
//	if (link->to == node)
//		return (-(link->capacity));
//	return (FLOW_ERROR);
//}

///**
// * @brief check if node a has an active link to node b
// * @param a; t_graph *
// * @param b; t_graph *
// */
//bool	ft_has_link(t_graph *a, t_graph *b)
//{
//	t_list	*current_link;

//	if (!a || !b)
//		return (false);
//	current_link = a->links;
//	while (current_link)
//	{
//		if (((t_link *)(current_link->content))->active &&
//								ft_is_link(current_link->content, a, b))
//			return (true);
//		current_link = current_link->next;
//	}
//	return (false);
//}
