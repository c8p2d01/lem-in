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
void	ft_g_insert_single(t_graph *node, t_graph *next)
{
	if (node->gates == NULL)
	{
		node->gates = ft_calloc(2, sizeof(t_graph *));
		node->gates[0] = next;
		if (!ft_has_gate(node->gates[0], node))
			ft_g_insert_single(node->gates[0], node);
	}
	else
	{
		size_t size = ft_array_size((void **)node->gates);
		size_t newSize = size + 1;
		node->gates = ft_realloc(node->gates, sizeof(t_graph *) * size, sizeof(t_graph *) * (newSize + 1));
		t_graph *in = next;
		node->gates[size] = in;
		if (!ft_has_gate(node->gates[size], node))
			ft_g_insert_single(node->gates[size], node);
	}
}

/**
 * @brief Insert one node to other nodes
 */
void	ft_g_insert(t_graph *node, size_t amount, ...)
{
	va_list c;
	va_start(c, amount);
	if (node->gates == NULL)
	{
		node->gates = ft_calloc((amount + 1), sizeof(t_graph *));
		node->gates[amount] = NULL;
		for (size_t i = 0; i < amount; i++)
		{
			node->gates[i] = va_arg(c, t_graph*);
			if (!ft_has_gate(node->gates[i], node))
			{
				ft_g_insert(node->gates[i], 1, node);
			}
		}
	}
	else
	{
		size_t size = ft_array_size((void **)node->gates);
		size_t newSize = size + amount;
		node->gates = ft_realloc(node->gates, sizeof(t_graph *) * size, sizeof(t_graph *) * (newSize + 1));
		while (size < newSize)
		{
			t_graph *in = va_arg(c, t_graph*);
			if (!in)
				break;
			node->gates[size] = in;
			if (!ft_has_gate(node->gates[size], node))
				ft_g_insert(node->gates[size], 1, node);
			size++;
		}
	}
}