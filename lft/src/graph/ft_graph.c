/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:08:04 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/15 22:33:54 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

/**
 * @brief Allocate a new node
 */
t_graph	*ft_g_new_node(char *data)
{
	t_graph *res = malloc(sizeof(t_graph), 1);
	res->links = NULL;
	res->name = data;
	res->x = 0;
	res->y = 0;
	res->lvl = -1;
	return (res);
}

void	ft_g_clean(t_graph *node)
{
	size_t amount = 0;
	while (node->gates[amount] != NULL)
		amount++;
	t_graph **comp = ft_calloc((amount + 1), sizeof(t_graph*));
	for (size_t i = 0; i < amount; i++)
	{
		int a = 0;
		while (comp[a] != NULL && comp[a] != node->gates[i])
			a++;
		if (comp[a])
			continue;
		while (comp[a] != NULL)
			a++;
		comp[a] = node->gates[i];
	}
}

/**
 * @brief Check if a node is already connected to another node
 */
bool	ft_has_gate(t_graph *node, t_graph *next)
{
	if (node == NULL || node->links == NULL)
		return (false);
	for (int i = 0; node->links && node->links[i]; i++)
	{
		if ((next == (node->links[i])->next && node != (node->links[i])->prev) || 
			((next == (node->links[i])->next) && node != (node->links[i])->prev))
			return(true);
	}
	return (false);
}

/**
 * @brief Print all nodes and its links
 * @note Debug
 */
void	print_nodes(t_graph **node)
{
	for (size_t i = 0; node[i]; ++i)
	{
		printf("node '%s'		level  %li\n", node[i]->name, node[i]->lvl);
		for (size_t j = 0; node[i]->links && node[i]->links[j]; ++j)
		{
			printf("\t link to '%s'\n", node[i]->links[j]->next->name);
		}
	}
}
