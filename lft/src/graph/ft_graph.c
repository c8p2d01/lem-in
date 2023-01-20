/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:08:04 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/14 15:25:46 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_room.h"

/**
 * @brief Allocate a new node
 */
t_room	*ft_g_new_node(char *data)
{
	t_room *res = ft_calloc(sizeof(t_room), 1);
	res->name = data;
	res->x = 0;
	res->y = 0;
	res->lvl = -1;
	return (res);
}

void	ft_g_clean(t_room *node)
{
	size_t amount = 0;
	while (node->links[amount] != NULL)
		amount++;
	t_room **comp = ft_calloc((amount + 1), sizeof(t_room*));
	for (size_t i = 0; i < amount; i++)
	{
		int a = 0;
		while (comp[a] != NULL && comp[a] != node->links[i])
			a++;
		if (comp[a])
			continue;
		while (comp[a] != NULL)
			a++;
		comp[a] = node->links[i];
	}
}

/**
 * @brief Check if a node is already connected to another node
 */
bool	ft_has_gate(t_room *node, t_room *next)
{
	if (node == NULL || node->links == NULL)
		return (false);
	for (int i = 0; node->links && node->links[i]; i++)
	{
		if (next == node->links[i])
			return(true);
	}
	return (false);
}

/**
 * @brief Print all nodes and its links
 * @note Debug
 */
void	print_nodes(t_room **node)
{
	for (size_t i = 0; node[i]; ++i)
	{
		printf("node '%s'		level  %li\n", node[i]->name, node[i]->lvl);
		for (size_t j = 0; node[i]->links && node[i]->links[j]; ++j)
		{
			printf("\t link to '%s'\n", node[i]->links[j]->name);
		}
	}
}
