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

#include "ft_graph.h"

/**
 * @brief Allocate a new node
 */
t_room	*ft_g_new_room(char *name)
{
	t_room *res = ft_calloc(sizeof(t_room), 1);
	if (res == NULL)
		return (NULL);
	*res = (t_room){
		.links = NULL,
		.name = name,
		.x = 0,
		.y = 0,
		.first_lvl = -1,
		.after_lvl = -1,
		.flown = false
	};
	return (res);
}

void	dry(t_room **all)
{
	for (int i = 0; all[i]; i++)
	{
		all[i]->flown = false;
	}
}

/**
 * @brief Print all the nodes and their links
 * @note For debug purposes
*/

void	print_nodes(t_room **node)
{
	t_room	*current = NULL;
	t_link	*linked = NULL;

	for (size_t i = 0; (current = node[i]) != NULL; ++i)
	{
		ft_printf("node '%s'\t\tfirst_level %i\n", node[i]->name, node[i]->first_lvl);
		ft_printf("node %p\tafter_level %i\n", node[i], node[i]->after_lvl);
		for (size_t j = 0; node[i]->links && (linked = node[i]->links[j]); ++j)
		{
			if (linked->active)
				ft_printf("\t link to '%s'\tflow %i\n",
						ft_otherside(linked, node[i])->name,
						ft_flow(linked, current));
		}
	}
}



void	print_node(t_room *node)
{
	t_link	*linked = NULL;

	ft_printf("node '%s'\t\tfirst_level %i\n", node->name, node->first_lvl);
	ft_printf("node %p\tafter_level %i\n", node, node->after_lvl);
	for (size_t j = 0; node->links && (linked = node->links[j]); ++j)
	{
		if (linked->active)
			ft_printf("\t link to '%s'\tflow %i\n",
				ft_otherside(linked, node)->name,
				ft_flow(linked, node));
	}
	
}
