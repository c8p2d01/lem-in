#include "../../inc/lem_in.h"

/**
 * @brief set the links to inactive
 * as we need to parse through the net several times
 * it only makes sense to not link and unlink every time
 * therefore links have a bool determining their existence
 * their memory is only cleared at the end of the program
 */
void	ft_unlink_graphs(t_graph *a, t_graph *b)
{
	t_list	*i;
	t_link	*link;

	if (!a || !b)
		return ;
	i = a->links;
	while (i)
	{
		link = i->content;
		if (link && link->active \
			&& ((link->from == a && link->to == b) || \
				(link->from == b && link->to == a)))
			link->active = false;
		i = i->next;
	}
	i = b->links;
	while (i)
	{
		link = i->content;
		if (link && link->active \
			 && (link->from == a && link->to == b) || \
				(link->from == b && link->to == a))
			link->active = false;
		i = i->next;
	}
}
