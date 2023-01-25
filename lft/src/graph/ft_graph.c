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
		.after_lvl = -1
	};
	return (res);
}

/**
 * @brief Print all the nodes and their links
 * @note For debug purposes
*/
void	print_nodes(t_room **node)
{
	for (size_t i = 0; node[i]; ++i)
	{
		printf("node '%s'\tfirst_level %li\n", node[i]->name, node[i]->first_lvl);
		printf("node '%s'\tafter_level %li\n", node[i]->name, node[i]->after_lvl);
		for (size_t j = 0; node[i]->links && node[i]->links[j]; ++j)
		{
			if (node[i]->links[j]->active)
				printf("\t link to '%s'\tflow %d\n", ft_otherside(node[i]->links[j], node[i])->name, ft_flow(node[i]->links[j], node[i]));
		}
	}
}

