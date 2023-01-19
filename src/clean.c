/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:50:26 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/14 18:39:28 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"
/* 
	if the node has a level of -1 -> it is not connected to start / end in any way it can be deleted
		->initial
	to clean the graph net we can then disconnect nodes of equal level from each other
		->initial
	then if the node has only connections to nodes with lower level we could delete that node entirely
		->recursively									^^here: not delete, but entirely disconnect, free in the end
*/

void	unlink_equals(t_graph *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (node->gates && node->gates[i])
	{
		if ((node->gates[i])->lvl == node->lvl)
			ft_g_unlink(node, node->gates[i]);
		else
			i++;
	}
}
/* 
set the level of dead end nodes and dead end chains to -1 so they get removed in (f*)level_sort()
 */
void	dead_ends(t_graph *node, globe *data)
{
	int	i;
	int	r;

	if (!node)
		return ;
	i = 0;
	while (node->gates && node->gates[i])
	{
		if (node->gates[i] == data->end || node->gates[i] == data->start)
			break;
		if ((node->gates[i])->lvl <= node->lvl)
			break;
		i++;
	}
	if (i > 0 && node->gates && !node->gates[i])
	{
		r = 0;
		while(node->gates[r])
		{
			dead_ends(node->gates[r], data);
			ft_g_unlink(node, node->gates[r]);
		}
		node->lvl = -1;
	}
}