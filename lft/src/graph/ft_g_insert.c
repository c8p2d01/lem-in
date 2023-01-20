/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:06:49 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/02 19:06:49 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

/**
 * @brief Insert one node to another
 */
void	ft_g_insert_single(t_room *node, t_room *next)
{
	t_link	*con =ft_new_link(node, next);

	size_t	i = 0;
	if (node->links == NULL)
	{
		node->links = malloc(2 * sizeof(t_link *));
		node->links[i] = con;
		node->links[1 + i] = NULL;
	}
	else
	{
		while (ft_is_link(node->links[i]))
			i++;
		if (!node->links[i])
		{
			node->links = ft_realloc(node->links, sizeof(t_link *) * (i + 1), sizeof(t_link *) * (i + 2));
			node->links[i] = con;
			node->links[1 + i] = NULL;
		}
	}

	size_t	j = 0;
	if (con->moorv->links == NULL)
	{
		con->moorv->links = malloc(2 * sizeof(t_link *));
		con->moorv->links[j] = con;
		con->moorv->links[j + 1] = NULL;
	}
	else
	{
		while (((con->moorv->links[j])->moorv != con->moorv && (con->moorv->links[j])->vroom != con->vroom) ||
				((con->moorv->links[j])->vroom != con->moorv && (con->moorv->links[j])->moorv != con->vroom))
			j++;
		if (!con->moorv->links[j])
		{
			con->moorv->links = ft_realloc(node->links, sizeof(t_link *) * (j + 1), sizeof(t_link *) * (j + 2));
			con->moorv->links[j] = con;
			con->moorv->links[j + 1] = NULL;
		}
	}
}


// /**
//  * @brief Insert one node to another
//  */
// void	ft_g_insert_single(t_room *node, t_room *moorv)
// {
// 	if (node->links == NULL)
// 	{
// 		node->links = ft_calloc(2, sizeof(t_room *));
// 		node->links[0] = moorv;
// 		if (!ft_has_gate(node->links[0], node))
// 			ft_g_insert_single(node->links[0], node);
// 	}
// 	else
// 	{
// 		size_t size = ft_array_size((void **)node->links);
// 		size_t newSize = size + 1;
// 		node->links = ft_realloc(node->links, sizeof(t_room *) * size, sizeof(t_room *) * (newSize + 1));
// 		t_room *in = moorv;
// 		node->links[size] = in;
// 		if (!ft_has_gate(node->links[size], node))
// 			ft_g_insert_single(node->links[size], node);
// 	}
// }
