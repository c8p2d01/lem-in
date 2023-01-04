/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:08:04 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/04 15:24:56 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

/**
 * @brief Allocate a new node
 */
t_graph	*ft_g_new_node(char *data)
{
	t_graph *res = ft_calloc(sizeof(t_graph), 1);
	res->name = data;
	res->x = 0;
	res->y = 0;
	res->lvl = -1;
	res->path_id = -1;
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
		printf("node '%s'		level %li		path id: %li\n", node[i]->name, node[i]->lvl, node[i]->path_id);
		for (size_t j = 0; node[i]->gates && node[i]->gates[j]; ++j)
		{
			printf("\t link to '%s'\n", node[i]->gates[j]->name);
		}
	}
}

/*
	delete a single node, and all refrences to it from other print_nodes
 */
void	ft_g_del_node(t_graph *node)
{
	size_t	i;
	size_t	l;
	bool	t;

	i = 0;
	while (node->gates && node->gates[i])
	{
		l = 0;
		t = false;
		while ((node->gates[i])->gates && (node->gates[i])->gates[l])
		{
			if ((node->gates[i])->gates[l] == node)
			{
				t = true;
			}
			if (t)
			{
				if ((node->gates[i])->gates[l + 1])
					(node->gates[i])->gates[l] = (node->gates[i])->gates[l + 1];
				else
					(node->gates[i])->gates[l] = NULL;
			}
			l++;
		}
		i++;
	}
	free(node->name);
	if (node->gates)
		free(node->gates);
}
