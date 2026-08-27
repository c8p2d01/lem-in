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
		graph->pos.x = rand();
		graph->pos.y = rand();
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

void	repulsion(bool draw)
{
	t_net		*net;
	t_hook		*p;
	t_qt_node	*root;
	t_list		*i;
	t_graph		*graph;

	p = *vis();
	net = *catch();
	root = new_qt_root(new_vec2d(p->min_x, p->max_x), new_vec2d(p->min_y, p->max_y), ft_lstsize(net->graph_nodes));
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		if (graph && graph->active)
			qt_insert(root, graph);
		i = i->next;
	}
	qt_mass(root);
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		if (graph && graph->active)
			qt_repulsion(root, i->content);
		i = i->next;
	}
	if (draw)
		qt_plot(root, true, false);
	qt_destroy(root);
}

static void	add_link_force(t_graph *a, t_graph *b, \
						t_vec2d *direction, double force)
{
	normalise2d(direction);
	a->f.x -= force * direction->x;
	a->f.y -= force * direction->y;
	b->f.x += force * direction->x;
	b->f.y += force * direction->y;
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

	if (link->flow != 0)
		add_link_force(a, b, &spring, 
			K_SPRING * (dst - (net->ideal_node_distance)) / dst);
	else
		add_link_force(a, b, &spring, 
			0.25 * K_SPRING * (dst - (net->ideal_node_distance)) / dst);
}

void	ends_repell()
{
	t_net	*net;
	t_graph	*a;
	t_graph	*b;
	t_vec2d	spring;
	double	dst;

	net = *catch();
	a = net->start;
	b = net->end;
	spring = connect2d(a->pos, b->pos);
	dst = veclen2d(&spring);
	add_link_force(a, b, &spring, 
		K_SPRING * (dst - (WDTH)) / dst);
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

t_vec2d	apply_forces()
{
	t_net	*net;
	t_list	*i;
	t_graph	*graph;
	t_vec2d	total;
	size_t	count;

	net = *catch();
	i = net->graph_nodes;
	total.x = 0;
	total.y = 0;
	count = 0;
	while (i)
	{
		graph = i->content;
		graph->v.x = graph->v.x * 0.4 + graph->f.x;
		graph->v.y = graph->v.y * 0.4 + graph->f.y;
		graph->pos.x += graph->v.x;
		graph->pos.y += graph->v.y;
		total.x += fabs(graph->v.x);
		total.y += fabs(graph->v.y);
		i = i->next;
		count++;
	}
	total.x /= count; // possible div by 0
	total.y /= count;
	return (total);
}

t_vec2d	calculate_forces(bool plot)
{
	t_hook		*params;
	t_net		*net;
	mlx_image_t	*img;
	static int	s;

	params = *vis();
	net = *catch();

	//scale_positions();
	determine_max_coordinates();
	corner_important();
	force_reset();

	repulsion(plot);
	attraction();
	if (plot)
	{
		img = ft_lstlast(params->images)->content;
		draw_links(params, img);
		draw_nodes(params, color_by_path, img);
	}

	return (apply_forces());
}

void	animate(size_t min_steps, size_t max_steps, size_t plot_frequency)
{
	t_net	*net;
	t_vec2d	heat;
	double	avg;
	double	curr;
	size_t	i;

	net = *catch();
	if (net->animate != true)
		return;
	avg = 0;
	i = 0;
	while (i < max_steps)
	{
		print_progress(i, max_steps - 1);
		heat = calculate_forces(i % plot_frequency == 0);
		curr = veclen2d(&heat);
		avg = 9 * avg + curr;
		avg /= 10;
		i++;
		if (i < min_steps)
			continue;
		if ((int)(avg * 10000) == (int)(curr * 10000))
			return ;
	}
}
