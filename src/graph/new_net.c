/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:08:04 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/12/19 21:48:17 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

/**
 * @brief a pseudo global: a static pointer variable that is returned by address
 * any calling function can change its values
 */
t_net	**catch()
{
	static t_net	*net;

	if (!net)
		net = ft_new_net();

	return(&net);
}
/**
 * @brief Allocate a new node
 */
t_net	*ft_new_net()
{
	t_net *res;

	res = ft_malloc(sizeof(t_net));
	if (res == NULL)
		return (NULL);
	*res = (t_net){
		.graph_nodes = NULL,
		.graph_links = NULL,
		.start = NULL,
		.end = NULL,
		.n_paths = 0,
		.paths = NULL,
		.packets = -1,
		.ideal_node_distance = 1,
		.file = NULL,
		.lines = 0,
		.display = DISPLAY,
		.animate = ANIMATE
	};
	return (res);
}
