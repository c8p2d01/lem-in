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
 * @brief Insert one node to another
 */
t_link	*ft_g_insert(t_room *node, t_room *next)
{
	t_link	*con =ft_new_link(node, next);

	size_t	i = 0;
	if (node->links == NULL)
	{
		node->links = malloc(2 * sizeof(t_link *));
		node->links[i] = con;
		node->links[1 + i] = NULL;
	}
	else
	{
		while (!ft_is_link(node->links[i], con->moorv, con->moorv))
			i++;
		if (!node->links[i])
		{
			node->links = ft_realloc(node->links, sizeof(t_link *) * (i + 1), sizeof(t_link *) * (i + 2));
			node->links[i] = con;
			node->links[1 + i] = NULL;
		}
	}

	size_t	j = 0;
	if (con->moorv->links == NULL)
	{
		con->moorv->links = malloc(2 * sizeof(t_link *));
		con->moorv->links[j] = con;
		con->moorv->links[j + 1] = NULL;
	}
	else
	{
		while (!ft_is_link(con->moorv->links[j], con->moorv, con->moorv))
			j++;
		if (!con->moorv->links[j])
		{
			con->moorv->links = ft_realloc(node->links, sizeof(t_link *) * (j + 1), sizeof(t_link *) * (j + 2));
			con->moorv->links[j] = con;
			con->moorv->links[j + 1] = NULL;
		}
	}
}
