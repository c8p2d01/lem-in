#include "../inc/lem_in.h"

bool flow(t_room *node, globe *data)
{
	if (node == NULL)
		return false;
	if (node == data->start)
		return true;
	t_room *next = NULL;
	t_room *other = NULL;
	t_link *link = NULL;
	for (int i = 0; node->links[i]; i++)
	{
		if (!node->links[i]->active)
			continue;
		other = ft_otherside(node->links[i], node);
		if (node == data->end)
		{
			if ((!next || other->lvl < next->lvl) && ft_flow(node->links[i], node) == 0)
			{	
				next = other;
				link = node->links[i];
			}
		}
		else
		{
			if (other != data->end && other != data->start && other->lvl <= node->lvl && ft_flow(node->links[i], node) == 1)
			{
				next = other;
				link = node->links[i];
				break ;
			}
			else if ((!next || other->lvl < next->lvl) && ft_flow(node->links[i], node) < 1)
			{
				next = other;
				link = node->links[i];
			}	
		}
	}
	if (!next)
		return (false);
	printf("%s -> node : %s\n", node->name, next->name);\
	ft_setflow(link, next);
	if (!flow(next, data))
	{
		ft_resetflow(link, next);
		return (false);
	}
	return (true);
}