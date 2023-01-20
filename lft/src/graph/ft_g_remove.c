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
 * @brief Deactive a link between 2
 */
void	ft_g_unlink(t_room *a, t_room *b)
{
	size_t	i;

	if (!a || !b)
		return ;
	i = 0;
	while (a->links && a->links[i])
	{
		if (ft_is_link(a->links[i], a, b))
			(a->links[i])->active = false;
		i++;
	}
}

/**
 * @brief Delete a node and deactive all links to it
 */
void	ft_g_del_node(t_room *node)
{
	size_t	i;

	if (!node)
		return ;
	i = 0;
	while (node->links && node->links[i])
	{
		(node->links[i])->active = false;
		i++;
	}
	if (node->name)
		free(node->name);
	if (node->links)
		free(node->links);
	free(node);
}
