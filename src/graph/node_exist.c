#include "../../inc/lem_in.h"

/**
 * @brief check in all allocated nodes if one exists
 * @param name : the name used for the comparison
 */
t_graph	*ft_node_exist(char *name)
{
	t_net	*net;
	t_list	*i;
	t_graph	*node;

	if (!name)
		return (NULL);
	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		node = i->content;
		if (node && ft_strlcmp(node->name, name, ft_strlen(name)) == 0)
			return (node);
		i = i->next;
	}
	return (NULL);
}
