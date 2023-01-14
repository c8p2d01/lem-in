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

/* 
remove a link between two nodes
 */
void	ft_g_unlink(t_graph *a, t_graph *b)
{
	int i;
	bool t;

	if (!a || !b)
		return;
	i = 0;
	t = false;
	while (a->gates && a->gates[i])
	{
		if (a->gates[i] == b)
			t = true;
		if (t)
			a->gates[i] = a->gates[i + 1];
		i++;
	}
	if (t)
		ft_g_unlink(b, a);

	// i = 0;
	// t = false;
	// while (b->gates && b->gates[i])
	// {
	// 	if (b->gates[i] == a)
	// 		t = true;
	// 	if (t)
	// 		b->gates[i] = b->gates[i + 1];
	// }
}

/*
	delete a single node, and all refrences to it from other print_nodes
*/
void	ft_g_del_node(t_graph *node)
{
	size_t	i;
	size_t	l;
	bool	t;

	if (!node)
		return ;
	i = 0;
	while (node->gates && node->gates[i])
	{
		l = 0;
		t = false;
		while ((node->gates[i])->gates && (node->gates[i])->gates[l])
		{
			if ((node->gates[i])->gates[l] == node)
			{
				t = true;
			}
			if (t)
			{
				if ((node->gates[i])->gates[l + 1])
					(node->gates[i])->gates[l] = (node->gates[i])->gates[l + 1];
				else
					(node->gates[i])->gates[l] = NULL;
			}
			l++;
		}
		i++;
	}
	free(node->name);
	if (node->gates)
		free(node->gates);
}
