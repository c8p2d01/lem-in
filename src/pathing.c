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
		if (link->active && b->dist < 0 && ((link->from == a && link->flow != 1) || \
											(link->to == a && link->flow != -1)))
		{
			b->dist = dist;
			new = ft_lstnew(b);
			ft_lstadd_back(queue, new);
		}
		i = i->next;
	}
}

/**
 * begining from the start node set the dist variable of each
 * graph node to the distance from the start
 */
void	set_distances()
{
	t_net	*net;
	t_list	*queue;
	t_list	*new;
	t_graph	*current;

	net = *catch();
	net->start->dist = 0;
	queue = ft_lstnew(net->start);
	while(queue)
	{
		current = queue->content;
		append_uninitialised(current, &queue, current->dist + 1);
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

t_graph	*closer_neighbour(t_graph *a)
{
	t_list	*i;
	t_link	*link;
	t_graph	*b;
	t_graph	*closest;

	if (!a)
		return (NULL);
	closest = NULL;
	i = a->links;
	while (i)
	{
		link = (t_link *)i->content;
		b = ft_linked_to(a, link);
		if (!closest)
			closest = b;
		if (closest->dist > b->dist)
			closest = b;
		i = i->next;
	}
	return (closest);
}

void	path_linking(t_graph *a, t_graph *b)
{
	t_link	*link;

	link = ft_are_linked(a, b);
	if (!link)
		interrupt("flow set through inactive link\n");
	if (link->from == a)
	{
		if (link->flow == -1)
			link->active = false;
		else
			link->flow = 1;
	}
	if (link->from == b)
	{
		if (link->flow == 1)
			link->active = false;
		else
			link->flow = -1;
	}
}

void	set_path(t_list *path_nodes)
{
	t_net	*net;
	t_path	*new_path_collection;
	size_t	i;

	net = *catch();
	new_path_collection = ft_calloc(net->n_paths + 2, sizeof(t_path));
	i = 0;
	while (i < net->n_paths)
	{
		new_path_collection[i] = net->paths[i];
		i++;
	}
	new_path_collection[i].path_nodes = path_nodes;
	net->n_paths++;
}

void	trace_path()
{
	t_net	*net;
	t_list	*path_nodes;
	t_graph *current;
	t_list	*new;
	t_graph *next;

	net = *catch();
	current = net->end;
	while (current->dist > 0)
	{
		new = ft_lstnew(current);
		ft_lstadd_back(&path_nodes, new);
		next = closer_neighbour(current);
		printf("%s going to %p\n", current->name, next);
		path_linking(current, next);
		current = next;
	}
	if (current != net->start)
		printf("no new path found\n");
	new = ft_lstnew(current);
	ft_lstadd_back(&path_nodes, new);
	set_path(path_nodes);
}
