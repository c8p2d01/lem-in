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
			found = true;
		if (found)
			a->gates[i] = a->gates[i + 1];
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
	bool	found = false;

	if (!node)
		return ;
	for (size_t i = 0; node->gates && node->gates[i]; ++i)
	{
		found = false;
		for (size_t j = 0; node->gates[i]->gates && node->gates[i]->gates[j]; ++j)
		{
			if (node->gates[i]->gates[j] == node)
			{
				found = true;
			}
			if (found)
			{
				node->gates[i]->gates[j] = node->gates[i]->gates[j + 1];
			}
		}
	}
	if (node->name)
	{
		free(node->name);
	}
	if (node->gates)
	{
		free(node->gates);
	}
	free(node);
}
