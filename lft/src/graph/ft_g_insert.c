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

#include "ft_room.h"

/**
 * @brief Insert one node to another
 */
void	ft_g_insert_single(t_room *node, t_room *next)
{
	if (node->links == NULL)
	{
		node->links = ft_calloc(2, sizeof(t_room *));
		node->links[0] = next;
		if (!ft_has_gate(node->links[0], node))
			ft_g_insert_single(node->links[0], node);
	}
	else
	{
		size_t size = ft_array_size((void **)node->links);
		size_t newSize = size + 1;
		node->links = ft_realloc(node->links, sizeof(t_room *) * size, sizeof(t_room *) * (newSize + 1));
		t_room *in = next;
		node->links[size] = in;
		if (!ft_has_gate(node->links[size], node))
			ft_g_insert_single(node->links[size], node);
	}
}

/**
 * @brief Insert one node to other nodes
 */
void	ft_g_insert(t_room *node, size_t amount, ...)
{
	va_list c;
	va_start(c, amount);
	if (node->links == NULL)
	{
		node->links = ft_calloc((amount + 1), sizeof(t_room *));
		node->links[amount] = NULL;
		for (size_t i = 0; i < amount; i++)
		{
			node->links[i] = va_arg(c, t_room*);
			if (!ft_has_gate(node->links[i], node))
			{
				ft_g_insert(node->links[i], 1, node);
			}
		}
	}
	else
	{
		size_t size = ft_array_size((void **)node->links);
		size_t newSize = size + amount;
		node->links = ft_realloc(node->links, sizeof(t_room *) * size, sizeof(t_room *) * (newSize + 1));
		while (size < newSize)
		{
			t_room *in = va_arg(c, t_room*);
			if (!in)
				break;
			node->links[size] = in;
			if (!ft_has_gate(node->links[size], node))
				ft_g_insert(node->links[size], 1, node);
			size++;
		}
	}
}