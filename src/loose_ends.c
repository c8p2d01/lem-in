#include "../inc/lem_in.h"

/**
 * @brief count and return the number of active links of graph a
 */
size_t	n_links(t_graph *a)
{
	t_list	*i;
	size_t	n;

	if (!a)
		return 0;
	n = 0;
	i = a->links;
	while (i)
	{
		n += ((t_link*)i->content)->active;
		i = i->next;
	}
	return (n);
}

/**
 * @brief deactivate all links of graph a
 */
void	isolate_graph(t_graph *a)
{
	t_list	*i;

	if (!a)
		return ;
	i = a->links;
	while (i)
	{
		((t_link*)i->content)->active = false;
		i = i->next;
	}
}

/**
 * @brief deactivate all links of graphs that have only one link
 * @attention end and start are exempt from this, 
 * it recurses untill all loose end lines are deactivated
 */
size_t	isolate_endings()
{
	t_net	*net;
	size_t	pruned;

	net = *catch();
	t_list	*i;
	i = net->graph_nodes;
	pruned = 0;
	while (i)
	{
		if (n_links((t_graph *)(i->content)) == 1)
		{
			isolate_graph((t_graph *)(i->content));
			pruned++;
		}
		i = i->next;
	}
	if (pruned)
		pruned += isolate_endings();
	return (pruned);
}
