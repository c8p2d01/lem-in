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
void	ft_g_insert_single(t_graph *node, t_graph *next)
{
	t_link	*con = malloc(sizeof(t_link) * 1);

	con->next = next;
	con->prev = node;
	con->fCapa = 0;
	con->bCapa = 0;
	con->active = true;

	size_t	i = 0;
	if (node->links == NULL)
	{
		node->links = malloc(2 * sizeof(t_link *));
		node->links[i] = con;
		node->links[1 + i] = NULL;
	}
	else
	{
		while ((node->links[i]->next != con->next && node->links[i]->prev != con->prev) ||
				(node->links[i]->prev != con->next && node->links[i]->next != con->prev))
			i++;
		if (!node->links[i])
		{
			node->links = ft_realloc(node->links, sizeof(t_link *) * (i + 1), sizeof(t_link *) * (i + 2));
			node->links[i] = con;
			node->links[1 + i] = NULL;
		}
	}

	size_t	j = 0;
	if (con->next->links == NULL)
	{
		con->next->links = malloc(2 * sizeof(t_link *));
		con->next->links[j] = con;
		con->next->links[j + 1] = NULL;
	}
	else
	{
		while (((con->next->links[j])->next != con->next && (con->next->links[j])->prev != con->prev) ||
				((con->next->links[j])->prev != con->next && (con->next->links[j])->next != con->prev))
			j++;
		if (!con->next->links[j])
		{
			con->next->links = ft_realloc(node->links, sizeof(t_link *) * (j + 1), sizeof(t_link *) * (j + 2));
			con->next->links[j] = con;
			con->next->links[j + 1] = NULL;
		}
	}
}
