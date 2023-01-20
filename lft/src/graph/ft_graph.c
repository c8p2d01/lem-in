/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:08:04 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/14 15:25:46 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

/**
 * @brief Allocate and default initialize a new node
 */
t_graph	*ft_g_new_node(char *data)
{
	t_graph *res = ft_calloc(sizeof(t_graph), 1);
	*res = (t_graph){
		.gates = NULL,
		.next_gates = NULL,
		.prev_gates = NULL,
		.name = data,
		.x = 0,
		.y = 0,
		.lvl = -1,
		.path_id = -1
	};
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
	if (node == NULL || node->gates == NULL)
		return (false);
	for (int i = 0; node->gates && node->gates[i]; i++)
	{
		if (next == node->gates[i])
			return(true);
	}
	return (false);
}

/**
 * @brief Print all nodes and its gates
 * @note Debug
 */
void	print_nodes(t_graph **node)
{
	for (size_t i = 0; node[i]; ++i)
	{
		printf("node '%s'\tlevel %li\t\tpath id: %li\n", node[i]->name, node[i]->lvl, node[i]->path_id);
		for (size_t j = 0; node[i]->gates && node[i]->gates[j]; ++j)
		{
			printf("\t link to '%s'\n", node[i]->gates[j]->name);
		}
		for (size_t j = 0; node[i]->next_gates && node[i]->next_gates[j]; ++j)
		{
			printf("\t next node: '%s'\n", node[i]->next_gates[j]->name);
		}
		for (size_t j = 0; node[i]->prev_gates && node[i]->prev_gates[j]; ++j)
		{
			printf("\t prev node: '%s'\n", node[i]->prev_gates[j]->name);
		}
	}
}
