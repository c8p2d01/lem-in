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
	t_room	*current = NULL;
	t_link	*linked = NULL;

	for (size_t i = 0; (current = node[i]) != NULL; ++i)
	{
		printf("node '%s'\tfirst_level \e[38;5;%im%li\e[0m\n", node[i]->name, colorflow(node[i]->first_lvl), node[i]->first_lvl);
		printf("node '%s'\tafter_level \e[38;5;%im%li\e[0m\n", node[i]->name, colorflow(node[i]->after_lvl), node[i]->after_lvl);
		for (size_t j = 0; node[i]->links && node[i]->links[j]; ++j)
		{
			if (linked->active)
				ft_printf("\t link to \e[38;5;%im'%s'\e[0m\tflow %i\n", 
				colorflow(ft_otherside(linked, current)->lvl * 5), 
						ft_otherside(linked, node[i])->name,
						ft_flow(linked, current));
		}
	}
}

