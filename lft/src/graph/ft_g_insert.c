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
	t_link	*con = ft_new_link(node, next);
	size_t	i = 0;

	if (node->links == NULL)
	{
		node->links = ft_calloc(2, sizeof(t_link *));
		node->links[i] = con;
	}
	else
	{
		while (node->links[i] && !ft_is_link(node->links[i], con->moorv, con->vroom))
			i++;
		if (!node->links[i])
		{
			node->links = ft_realloc(node->links, sizeof(t_link *) * (i + 1), sizeof(t_link *));
			node->links[i] = con;
		}
	}

	i = 0;
	if (con->moorv->links == NULL)
	{
		con->moorv->links = ft_calloc(2, sizeof(t_link *));
		con->moorv->links[i] = con;
	}
	else
	{
		while (con->moorv->links[i] && !ft_is_link(con->moorv->links[i], con->moorv,  con->vroom))
			i++;
		if (!con->moorv->links[i])
		{
			con->moorv->links = ft_realloc(con->moorv->links, sizeof(t_link *) * (i + 1), sizeof(t_link *));
			con->moorv->links[i] = con;
		}
	}
	return (con);
}
