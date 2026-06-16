#include "../inc/lem_in.h"

void	jitter_positions()
{
	t_net	*net;
	t_list	*i;
	t_graph	*graph;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		if (graph->important != true)
		{
			if (graph->pos.x == graph->pos.y)
			{
				graph->pos.x += 0.01 * rand() / RAND_MAX;
				graph->pos.y -= 0.01 * rand() / RAND_MAX;
			}
		}
		i = i->next;
	}
	
}

void	force_reset()
{
	t_net	*net;
	t_list	*i;
	t_graph	*graph;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		graph->f.x = 0;
		graph->f.y = 0;
		i = i->next;
	}
}

// there is no need to run this function ?
void	velocity_reset()
{
	t_net	*net;
	t_list	*i;
	t_graph	*graph;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		graph->v.x = 0;
		graph->v.y = 0;
		i = i->next;
	}
}

void	repulsion()
{
	t_net		*net;
	t_hook		*p;
	t_qt_node	*root;
	t_list		*i;
	t_graph		*graph;

	p = *vis();
	net = *catch();
	determine_max_coordinates();
	root = new_qt_root(p->min_x, p->min_y, p->max_x, p->max_y);
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		if (graph)
			qt_insert(root, graph);
		i = i->next;
	}
	qt_mass(root);
	i = net->graph_nodes;
	while (i)
	{
		qt_repulsion(root, i->content);
		i = i->next;
	}
	qt_destroy(root);
}

static void	add_link_force(t_graph *a, t_graph *b, \
						t_vec2d *direction, double force)
{
	a->pos.x += force * direction->x;
	b->pos.x += force * direction->x;
	a->pos.y += force * direction->y;
	b->pos.y += force * direction->y;
}

void	link_force(t_link *link)
{
	t_graph	*a;
	t_graph	*b;
	t_vec2d	spring;
	double	dst;
	t_net	*net;

	net = *catch();
	a = link->from;
	b = link->to;
	spring = connect2d(a->pos, b->pos);
	dst = veclen2d(&spring);
	normalise2d(&spring);
	add_link_force(a, b, &spring, 
		K_SPRING * (dst - net->ideal_node_distance) / dst);
}

void	attraction()
{
	t_net	*net;
	t_list	*i;
	t_link	*link;

	net = *catch();
	i = net->graph_links;
	while (i)
	{
		link = i->content;
		link_force(link);
		i = i->next;
	}
}

void	apply_forces()
{
	t_net	*net;
	t_list	*i;
	t_graph	*graph;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		if (!graph->important)
		{
			graph->v.x = graph->v.x * 1 + graph->f.x;
			graph->v.y = graph->v.y * 1 + graph->f.y;
			graph->pos.x += graph->v.x;
			graph->pos.y += graph->v.y;
		}
		i = i->next;
	}
}

void	calculate_forces()
{
	force_reset();
	repulsion();
	attraction();
	apply_forces();
}
