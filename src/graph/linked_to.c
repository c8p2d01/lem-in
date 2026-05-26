#include "../../inc/lem_in.h"

/**
 * @brief return the node that is linked to by the link
 */
t_graph	*ft_linked_to(t_graph *a, t_link *link)
{
	if (!link || !a)
		return (NULL);
	if (link->from == a)
		return link->to;
	if (link->to == a)
		return link->from;
	return (NULL);
}
