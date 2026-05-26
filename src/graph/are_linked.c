#include "../../inc/lem_in.h"

/**
 * @brief check if the two given nodes already have an active link
 */
t_link	*ft_are_linked(t_graph *a, t_graph *b)
{
	t_list	*i;
	t_link	*link;

	if (!a || !b)
		return (NULL);
	i = a->links;
	while(i)
	{
		link = i->content;
		if (!link)
			break ;
		if (((link->from == a && link->to == b) || \
			(link->from == b && link->to == a)) &&
			link->active)
			return (link);
		i = i->next;
	}
	return (NULL);
}

// technically id need to check if both nodes have the link...
