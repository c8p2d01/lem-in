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
 * @brief Allocate a new node
 */
t_graph	*ft_new_graph(char *name, int x, int y)
{
	t_graph	*res;
	t_list	*list;
	t_net	*net;

	res = ft_malloc(sizeof(t_graph));
	if (res == NULL)
		return (NULL);
	*res = (t_graph){
		.links = NULL,
		.name = name,
		.dist = -1,
		.pos.x = x,
		.pos.y = y,
		.ant = 0,
		.path = -1,
		.important = false,
		.f.x = 0,
		.f.y = 0,
		.v.x = 0,
		.v.y = 0
	};
	net = *catch();
	list = ft_lstnew(res);
	ft_lstadd_back(&(net->graph_nodes), list);
	return (res);
}
