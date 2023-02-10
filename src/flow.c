#include "../inc/lem_in.h"

bool first_flow(t_room *node, globe *data)
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
		other = ft_otherside(node->links[i], node);
		if (!node->links[i]->active || other->first_lvl < 0)
			continue;
		if (node == data->end)
		{
			if ((!next || other->first_lvl < next->first_lvl) && ft_flow(node->links[i], node) == 0)
			{	
				next = other;
				link = node->links[i];
			}
		}
		else
		{
			if (other != data->end && other != data->start && other->first_lvl <= node->first_lvl && ft_flow(node->links[i], node) == -1)
			{
				next = other;
				link = node->links[i];
				break ;
			}
			else if ((!next || other->first_lvl < next->first_lvl) && ft_flow(node->links[i], node) == 0)
			{
				next = other;
				link = node->links[i];
			}	
		}
	}
	if (!next)
		return (false);
	printf("%s -> node : %s\n", node->name, next->name);
	if (!first_flow(next, data))
		return (false);
	ft_setflow(link, next);
	return (true);
}

bool after_flow(t_room *node, globe *data)
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
		other = ft_otherside(node->links[i], node);
		if (!node->links[i]->active || other->after_lvl < 0 || other == data->end)
			continue;
		if (node == data->end)
		{
			if ((!next || other->after_lvl < next->after_lvl) && ft_flow(node->links[i], node) == 0)
			{	
				next = other;
				link = node->links[i];
			}
		}
		else
		{
			if (ft_flow(node->links[i], node) == -1)
			{
				printf("node '%s'\t\tfirst_level %li\t\tother_node '%s'\t\tfirst_level %li\n", node->name, node->first_lvl, other->name, other->first_lvl);
				printf("node '%s'\t\tafter_level %li\t\tother_node '%s'\t\tafter_level %li\n", node->name, node->after_lvl, other->name, other->after_lvl);
			}
			/*if (other == data->start && ft_flow(node->links[i], node) == 0)
			{
				next = other;
				link = node->links[i];
				break ;
			}
			else*/ if (other != data->start &&/* (other->first_lvl <= node->first_lvl && other->after_lvl <= node->after_lvl) && */ft_flow(node->links[i], node) == -1)
			{
				next = other;
				link = node->links[i];
				break ;
			}
			else if (other->first_lvl < node->first_lvl && other->after_lvl == node->after_lvl && ft_flow(node->links[i], node) == 0)
			{
				next = other;
				link = node->links[i];
				//break;
			}
			else if (((!next && other->after_lvl < node->after_lvl) || (next && other->after_lvl < next->after_lvl)) && ft_flow(node->links[i], node) == 0)// maybe <= 
			{
				next = other;
				link = node->links[i];
			}
		}
	}
	if (next)
	{
		// printf("node '%s'\t\tfirst_level %li\t\tother_node '%s'\t\tfirst_level %li\n", node->name, node->first_lvl, next->name, next->first_lvl);
		// printf("node '%s'\t\tafter_level %li\t\tnext_node '%s'\t\tafter_level %li\n", node->name, node->after_lvl, next->name, next->after_lvl);
		printf("%s -> node : %s\n", node->name, next->name);
	}
	if (!next)
		return (false);
	//printf("%s -> node : %s\n", node->name, next->name);
	if (!after_flow(next, data))
		return (false);
	ft_setflow(link, next);
	return (true);
}