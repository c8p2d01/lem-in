#include "../inc/lem_in.h"

bool	first_flow(t_room *node, globe *data)
{
	if (node == NULL)
		return false;
	if (node == data->start)
		return true;
	t_room *next = NULL;
	t_room *other = NULL;
	t_link *link = NULL;

	for (int i = 0; node->links[i] != NULL; i++)
	{
		if (!node->links[i]->active)
			continue;
		other = ft_otherside(node->links[i], node);
		if (other == data->end)
			continue;
		if (other == data->start)
		{
			next = other;
			link = node->links[i];
			break ;
		}
		if ((!next && other->first_lvl < node->first_lvl) || (next && other->first_lvl < next->first_lvl))
		{
			next = other;
			link = node->links[i];
		}
	}
	if (!first_flow(next, data))
		return false;
	ft_setflow(link, next);
	return true;
}

bool after_flow(t_room *node, globe *data, int x)
{
	// if (x == 50)
	// 	return false;
	if (node == NULL)
		return false;
	if (node == data->start)
		return true;
	t_room *next = NULL;
	t_room *other = NULL;
	t_link *link = NULL;
	for (size_t i = 0; node->links[i]; i++)
	{
		if (!node->links[i]->active)
			continue;
		other = ft_otherside(node->links[i], node);
		if (other->after_lvl < 0 || other == data->end || ft_flow(node->links[i], node) == COUNTERFLOW)
		{
			continue;
		}
		if(ft_flow(node->links[i], node) == FORWARDFLOW)
		{
			if (node == data->end)
				continue;
			next = other;
			link = node->links[i];
			break ;
		}
		if (other == data->start && ft_flow(node->links[i], node) == NOFLOW)
		{
			next = other;
			link = node->links[i];
		}
		if (next != data->start)
		{
			if (!next && (other->after_lvl == node->after_lvl && other->first_lvl < node->first_lvl))
			{
				next = other;
				link = node->links[i];
			}
			else if (!next && (other->after_lvl < node->after_lvl))
			{
				next = other;
				link = node->links[i];
			}
			else if (next && (other->after_lvl < next->after_lvl))
			{
				next = other;
				link = node->links[i];
			}
		}
	}
	if (next)
		printf("%s[%zi] -%i> %s[%zi] \n",node->name, node->after_lvl, ft_flow(link, node), next->name, next->after_lvl);
	if (ft_flow(link, node) == -1)
	{
		ft_setflow(link, next);
		if (!after_flow(next, data, ++x))
		{
			ft_resetflow(link, next);
			return (false);
		}
	}
	else
	{
		if (!after_flow(next, data, ++x))
			return (false);
		ft_setflow(link, next);
	}
	return (true);
}