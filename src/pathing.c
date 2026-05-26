#include "../inc/lem_in.h"

void	append_uninitialised(t_graph *a, t_list **queue, size_t dist)
{
	t_list	*i;
	t_link	*link;
	t_graph	*b;
	t_list	*new;

	if (!a || !queue)
		return ;
	i = a->links;
	while(i)
	{
		link = (t_link *)(i->content);
		b = ft_linked_to(a, link);
				link = (t_link *)(i->content);
		b = ft_linked_to(a, link);
		if (link->active &&
			b->dist < 0 && !has_flow_from(b, link))
		{
			b->dist = dist;
			new = ft_lstnew(b);
			ft_lstadd_back(queue, new);
		}
		i = i->next;
	}
}

/**
 * begining from given node set the dist variable of each connected
 * graph node (under consideration of links with direction)to the distance from the start
 */
void	set_distances(t_graph	*start, size_t base, size_t increment)
{
	t_net	*net;
	t_list	*queue;
	t_list	*new;
	t_graph	*current;

	net = *catch();
	start->dist = base;
	queue = ft_lstnew(start);
	while(queue)
	{
		current = queue->content;
		current->path = 0;
		append_uninitialised(current, &queue, current->dist + increment);
		if (increment == 0)
			current->path = base;
		queue = queue->next;
	}
}

/**
 * dist variable of each graph node to -1
 */
void	reset_distances()
{
	t_net	*net;
	t_list	*i;
	t_graph	*a;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		a = (t_graph *)i->content;
		a->dist = -1;
		i = i->next;
	}
}

void	identify_nets()
{
	t_net	*net;
	t_list	*i;
	t_graph	*a;

	net = *catch();
	set_distances(net->start, 0, 0);
	i = net->graph_nodes;
	while (i)
	{
		a = (t_graph *)i->content;
		if (a->dist < 0)
		{
			net->n_paths++;
			set_distances(a, net->n_paths, 0);
		}
		i = i->next;
	}
	reset_distances();
}

void	prepare_pathing()
{
	t_net	*net;
	t_list	*i;
	size_t	count;

	net = *catch();
	i = net->end->links;
	count = 0;
	while (i)
	{
		count++;
		i = i->next;
	}
	net->paths = ft_calloc(sizeof(t_path), count + 1);
	net->n_paths = 0;
}

void	path_linking(t_graph *from, t_link *link)
{
	if (link->from == from)
	{
		if (link->flow == -1)
			link->active = false;
		else if (link->flow == 1)
			ft_printf("ERROR\t this case should never occur\n");
		else
			link->flow = 1;
	}
	else if (link->to == from)
	{
		if (link->flow == 1)
			link->active = false;
		else if (link->flow == -1)
			ft_printf("ERROR\t this case should never occur\n");
		else
			link->flow = -1;
	}
	else
		ft_printf("ERROR\t Closest link doesnt link correct nodes\n");
}

bool	has_flow_from(t_graph *from, t_link *link)
{
	if (link->from == from && link->flow > 0)
		return true;
	if (link->to == from && link->flow < 0)
		return true;
	return (false);
}

t_link	*closer_neighbour(t_graph *a)
{
	t_list	*i;
	t_link	*close;
	t_link	*i_link;
	t_graph	*c;
	t_graph	*b;

	i = a->links;
	close = NULL;
	while (i)
	{
		i_link = i->content;
		b = ft_linked_to(a, i_link);
		if (has_flow_from(a, i_link))
			;
		else if (i_link->active && (!close || b->dist < c->dist))
		{
			close = i_link;
			c = ft_linked_to(a, close);
		}
		i = i->next;
	}
	if (close)
		path_linking(a, close);
	return (close);
}

/**
 * traces paths, setting directions on links
 * if a link alreadz has a direction and it can be countered, deactivate the link
 */
void	trace_path()
{
	t_net	*net;
	t_link	*link;
	t_graph	*a;

	net = *catch();
	a = net->end;
	while (a && a->dist > 0)
	{
		link = closer_neighbour(a);
		a = ft_linked_to(a, link);
	}
}

void	map_paths()
{
	t_net	*net;

	net = *catch();
}
