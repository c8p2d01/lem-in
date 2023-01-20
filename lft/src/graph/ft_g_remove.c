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

#include "ft_room.h"

/* 
remove a link between two nodes
 */
void	ft_g_unlink(t_room *a, t_room *b)
{
	int i;
	bool t;

	if (!a || !b)
		return;
	i = 0;
	t = false;
	while (a->links && a->links[i])
	{
		if (a->links[i] == b)
			t = true;
		if (t)
			a->links[i] = a->links[i + 1];
		i++;
	}
	if (t)
		ft_g_unlink(b, a);

	// i = 0;
	// t = false;
	// while (b->links && b->links[i])
	// {
	// 	if (b->links[i] == a)
	// 		t = true;
	// 	if (t)
	// 		b->links[i] = b->links[i + 1];
	// }
}

/*
	delete a single node, and all refrences to it from other print_nodes
*/
void	ft_g_del_node(t_room *node)
{
	size_t	i;
	size_t	l;
	bool	t;

	if (!node)
		return ;
	i = 0;
	while (node->links && node->links[i])
	{
		l = 0;
		t = false;
		while ((node->links[i])->links && (node->links[i])->links[l])
		{
			if ((node->links[i])->links[l] == node)
			{
				t = true;
			}
			if (t)
			{
				if ((node->links[i])->links[l + 1])
					(node->links[i])->links[l] = (node->links[i])->links[l + 1];
				else
					(node->links[i])->links[l] = NULL;
			}
			l++;
		}
		i++;
	}
	free(node->name);
	if (node->links)
		free(node->links);
}
