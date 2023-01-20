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
 * @brief Remove link between two nodes
 */
void	ft_g_unlink(t_graph *a, t_graph *b)
{
	bool	found = false;

	if (!a || !b)
		return ;
	for (size_t i = 0; a->gates && a->gates[i]; ++i)
	{
		if (a->gates[i] == b)
		{
			ft_memmove(&a->gates[i], &a->gates[i + 1], sizeof(t_graph *) * (ft_array_size((void**)&a->gates[i + 1]) + 1));
			found = true;
			break;
		}
	}
	for (size_t i = 0; a->next_gates && a->next_gates[i]; ++i)
	{
		if (a->next_gates[i] == b)
		{
			ft_memmove(&a->next_gates[i], &a->next_gates[i + 1], sizeof(t_graph *) * (ft_array_size((void**)&a->next_gates[i + 1]) + 1));
			found = true;
			break;
		}
	}
	for (size_t i = 0; a->prev_gates && a->prev_gates[i]; ++i)
	{
		if (a->prev_gates[i] == b)
		{
			ft_memmove(&a->prev_gates[i], &a->prev_gates[i + 1], sizeof(t_graph *) * (ft_array_size((void**)&a->prev_gates[i + 1]) + 1));
			found = true;
			break;
		}
	}
	if (found)
	{
		ft_g_unlink(b, a);
	}
}

/**
 * @brief Delete a node and remove all links to it
 */
void	ft_g_del_node(t_graph *node)
{
	if (!node)
		return ;
	for (size_t i = 0; node->gates && node->gates[i]; ++i)
	{
		for (size_t j = 0; node->gates[i]->gates && node->gates[i]->gates[j]; ++j)
		{
			if (node->gates[i]->gates[j] == node)
			{
				ft_memmove(&node->gates[i]->gates[j], &node->gates[i]->gates[j + 1], sizeof(t_graph *) * (ft_array_size((void**)&node->gates[i]->gates[j + 1]) + 1));
				break;
			}
		}
		for (size_t j = 0; node->gates[i]->next_gates && node->gates[i]->next_gates[j]; ++j)
		{
			if (node->gates[i]->next_gates[j] == node)
			{
				ft_memmove(&node->gates[i]->next_gates[j], &node->gates[i]->next_gates[j + 1], sizeof(t_graph *) * (ft_array_size((void**)&node->gates[i]->next_gates[j + 1]) + 1));
				break;
			}
		}
		for (size_t j = 0; node->gates[i]->prev_gates && node->gates[i]->prev_gates[j]; ++j)
		{
			if (node->gates[i]->prev_gates[j] == node)
			{
				ft_memmove(&node->gates[i]->prev_gates[j], &node->gates[i]->prev_gates[j + 1], sizeof(t_graph *) * (ft_array_size((void**)&node->gates[i]->prev_gates[j + 1]) + 1));
				break;
			}
		}
	}
	if (node->name)
		free(node->name);
	if (node->gates)
		free(node->gates);
	if (node->next_gates)
		free(node->next_gates);
	if (node->prev_gates)
		free(node->prev_gates);
	free(node);
}
