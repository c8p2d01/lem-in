#include "../../inc/lem_in.h"

/**
 * @brief link one node to another
 * if a link already exists, set it to active as well
 */
t_link	*ft_link_graphs(t_graph *a, t_graph *b)
{
	t_link	*new_link;
	t_list	*i;

	if (!a || !b || !ft_node_exist(a->name) || !ft_node_exist(b->name))
		return (NULL);
	new_link = ft_are_linked(a, b);
	if (new_link == NULL)
	{
		new_link = ft_new_link(a, b);
		i = ft_lstnew(new_link);
		if (!i)
			return (NULL);
		ft_lstadd_back(&(a->links), i);
		i = ft_lstnew(new_link);
		if (!i)
			return (NULL);
		ft_lstadd_back(&(b->links), i);
	}
	new_link->active = true;
	return (new_link);
}
