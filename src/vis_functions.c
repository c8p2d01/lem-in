#include "../inc/lem_in.h"
#include "../MLX42/include/MLX42/MLX42.h"

void	draw_links(t_hook *params, mlx_image_t *img)
{
	t_net		*net;
	t_list		*i;
	t_link		*link;
	t_vec2d		from;
	t_vec2d		to;
	int			color;

	net = *catch();
	i = net->graph_links;
	while (i)
	{
		link = (t_link *)i->content;
		from = point_on_image(((t_graph *)(link->from))->pos);
		to = point_on_image(((t_graph *)(link->to))->pos);

		if (link->flow != 0)
		{
			color = create_rgbt(16, 16, 224, 255);
			if (!link->active)
				//color = create_rgbt(196, 32, 196, 255);
				color = 3290481919;
		}
		else
		{
			color = create_rgbt(128, 128, 128, 255);
			if (!link->active)
				color = create_rgbt(16, 16, 16, 255);
		}
		draw_line(img, from, to, color);
		i = i->next;
	}
}

void	draw_forces(t_hook *params, mlx_image_t *img, int color)
{
	t_net	*net;
	t_list	*i;
	t_graph	*graph;
	t_vec2d	p;
	t_vec2d	f;
	t_vec2d	v;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		graph = (t_graph *)i->content;
		p = point_on_image(graph->pos);
		f = sum2d(graph->pos, graph->f);
		f = point_on_image(f);
		draw_line(img, p, f, color);
		i = i->next;
	}
}

void	draw_nodes(t_hook *params, int(f)(t_graph *), mlx_image_t *img)
{
	t_net	*net;
	t_list	*i;
	t_graph	*graph;
	t_vec2d	p;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		graph = (t_graph *)i->content;
		p = point_on_image(graph->pos);
		draw_square(img, p, NODE_SIZE, f(graph) << 8 | 255);
		i = i->next;
	}
}

int	color_by_path(t_graph *a)
{
	t_net		*net;
	float		max;
	float		fraction;
	float		dist;
	int			color;

	net = *catch();
	if (a == net->start)
		return(create_rgbt(255, 255, 255, 255));
	if (a == net->end)
		return(create_rgbt(0, 0, 0, 255));
	if (a->path < 0)
		return (create_rgbt(255, 42, 42, 42));
	max = net->n_paths;
	dist = (float)a->path;
	if (dist < 0)
		dist += max;
	fraction = dist / (float)(max);
	if (fraction < 0)
		fraction += 1;
	color = create_multi_gradient(fraction, 6, 0,255,255, 0,0,255, 255,0,255, 255,0,0, 255,255,0, 0,255,0);
	return (color);
}

int	color_by_distance(t_graph *a)
{
	t_net		*net;
	float		max;
	float		fraction;
	float		dist;

	net = *catch();
	max = net->end->dist - net->start->dist;
	dist = (float)a->dist;
	if (dist < 0)
		return (color_by_path(a));
	fraction = (float)a->dist / (float)(max);
	if (fraction < 0)
		fraction += 1;
	int color = create_multi_gradient(fraction, 4, 255,0,0, 255,255,0, 0,255,0, 0,255,255, 0,0,255, 255,0,255);
	return (color);
}

int	color_by_ant(t_graph *a)
{
	t_net		*net;
	size_t		max;
	float		fraction;

	net = *catch();
	if (a == net->end)
		return (create_rgbt(255, 255, 255, 255));
	if (a == net->start)
		return (create_rgbt(255, 255, 255, 255));
	if (a->ant < 0)
		return (create_rgbt(255, 42, 42, 42));
	max = net->packets;
	fraction = (float)a->ant / (float)(max);
	if (fraction < 0)
		fraction += 1;
	int color = create_multi_gradient(fraction, 6, 255,0,0, 255,255,0, 0,255,0, 0,255,255, 0,0,255, 255,0,255);
	return (color);
}

void	plot_graph(int(f)(t_graph *))
{
	t_net		*net;
	t_hook		*params;
	mlx_image_t	*img;
	t_list		*new;

	net = *catch();
	if (net->display == false)
		return ;
	determine_max_coordinates();
	params = *vis();
	img = mlx_new_image(params->mlx, WDTH, HGHT);
	if (!img)
		interrupt("images failed\n");
	draw_links(params, img);
	draw_nodes(params, f, img);
	new = ft_lstnew(img);
	if (!new)
		interrupt("images failed\n");
	ft_lstadd_back(&params->images, new);
	params->n_images++;
}
