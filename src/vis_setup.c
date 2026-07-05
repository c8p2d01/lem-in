#include "../inc/lem_in.h"
#include "../MLX42/include/MLX42/MLX42.h"

int		create_rgbt(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_hook	**vis()
{
	static t_hook	*res;
	if (res == NULL)
	{
		res = ft_malloc(sizeof(t_hook));
		*res = (t_hook){
			.mlx = mlx_init(WDTH, HGHT, "Graph-network", true),
			.images = NULL,
			.n_images = 0,
			.max_x = ft_atof("-200000000000"),
			.max_y = ft_atof("-200000000000"),
			.min_x = ft_atof("200000000000"),
			.min_y = ft_atof("200000000000"),
			.press = false
		};
		determine_max_coordinates();
		mlx_loop_hook(res->mlx, keyhook, res);
	}
	return (&res);
}

void	keyhook(void *param)
{
	t_hook			*params;
	
	params = (t_hook*)param;
	if (mlx_is_key_down(params->mlx, MLX_KEY_ESCAPE))
		interrupt("");
	else if (mlx_is_key_down(params->mlx, MLX_KEY_P))
	{
		net_to_file(-42);
		interrupt("");
	}
	else if (params->press == false && mlx_is_key_down(params->mlx, MLX_KEY_RIGHT))
	{
		params->press = true;
		if (!params->images->next)
		{
			animate(1, 50, 10);
		}
		if (params->images->next && params->n_images > 1)
		{
			params->images = params->images->next;
			if (params->images->content)
			{
				mlx_delete_image(params->mlx, params->images->prev->content);
				mlx_image_to_window(params->mlx, params->images->content, 0, 0);
			}
			params->n_images--;
		}
		else
			interrupt("end reached\n");
	}
	else if (!mlx_is_key_down(params->mlx, MLX_KEY_RIGHT))
		params->press = false;
}

static void	reset_max_coordinates()
{
	t_hook	*params;

	params = *vis();
	params->max_x = ft_atof("-200000000000");
	params->max_y = ft_atof("-200000000000");
	params->min_x = ft_atof("200000000000");
	params->min_y = ft_atof("200000000000");
}

void	determine_max_coordinates()
{
	t_net	*net;
	t_hook	*params;
	t_list	*i;
	t_graph	*graph;

	net = *catch();
	params = *vis();
	i = net->graph_nodes;
	reset_max_coordinates();
	while (i)
	{
		graph = (t_graph *)i->content;
		if (graph->pos.x < params->min_x)
			params->min_x = graph->pos.x;
		if (graph->pos.y < params->min_y)
			params->min_y = graph->pos.y;
		if (graph->pos.x > params->max_x)
			params->max_x = graph->pos.x;
		if (graph->pos.y > params->max_y)
			params->max_y = graph->pos.y;
		i = i->next;
	}
	params->diffs.x = params->max_x - params->min_x;
	params->diffs.y = params->max_y - params->min_y;
}

t_vec2d	point_on_image(t_vec2d pos)
{
	t_vec2d	res;
	t_hook	*params;

	params = *vis();
	res.x = (pos.x - params->min_x) / params->diffs.x;
	res.y = (pos.y - params->min_y) / params->diffs.y;
	res.x *= (WDTH - (2 * FRAME));
	res.y *= (WDTH - (2 * FRAME));
	res.x += FRAME;
	res.y += FRAME;
	return (res);
}

double	average_link_count()
{
	t_net		*net;
	t_list		*i;
	t_graph		*graph;
	double		total;
	size_t		count;

	net = *catch();
	i = net->graph_nodes;
	total = 0.0;
	count = 0;
	while (i)
	{
		graph = i->content;
		total += ft_lstsize(graph->links);
		count++;
		i = i->next;
	}
	return (total / count);
}

void	average_link_distance()
{
	t_net		*net;
	t_list		*i;
	t_link		*link;
	double		total;
	size_t		count;
	t_vec2d		spring;

	net = *catch();
	i = net->graph_links;
	count = 0;
	total = 0.0f;
	while (i)
	{
		link = i->content;
		spring = connect2d(link->from->pos, link->to->pos);
		total += veclen2d(&spring);
		i = i->next;
		count ++;
	}
	net->ideal_node_distance = (total / count) / (average_link_count() - 1);
}

void	corner_important()
{
	t_net		*net;
	t_hook		*params;

	net = *catch();
	params = *vis();
	net->end->pos.x = params->max_x;
	net->end->pos.y = params->max_y;
	net->start->pos.x = params->min_x;
	net->start->pos.y = params->min_y;
}

void	scale_positions()
{
	t_net		*net;
	t_list		*i;
	t_graph		*graph;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		graph = i->content;
		graph->pos = point_on_image(graph->pos);
		graph->pos.x -= FRAME;
		graph->pos.y -= FRAME;
		i = i->next;
	}
}

void	draw_square(mlx_image_t *img, t_vec2d p, size_t len, int color)
{
	size_t	x0;
	size_t	y0;
	size_t	x1;
	size_t	y1;

	x0 = p.x - len / 2;
	x1 = p.x + len / 2;
	while (x0 < WDTH && x0 < x1)
	{
		y0 = p.y - len / 2;
		y1 = p.y + len / 2;
		while (y0 < HGHT && y0 < y1)
		{
			mlx_put_pixel(img, x0, y0, color);
			y0++;
		}
		x0++;
	}
}

void	truncate_vec(t_vec2d *p)
{
	p->x = (int)p->x;
	p->y = (int)p->y;
}

void	draw_line(mlx_image_t *img, t_vec2d p1, t_vec2d p2, int color)
{
	truncate_vec(&p1);
	truncate_vec(&p2);
	int dx = abs(p2.x - p1.x);
	int dy = -abs(p2.y - p1.y);
	int sx = p1.x < p2.x ? 1 : -1;
	int sy = p1.y < p2.y ? 1 : -1;
	int error = dx + dy;
	int e2;

	while (1)
	{
		if (p1.x >= 0 && p1.x < WDTH && p1.y >= 0 && p1.y < HGHT)
			mlx_put_pixel(img, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			error += dy;
			p1.x += sx;
		}
		if (e2 <= dx)
		{
			error += dx;
			p1.y += sy;
		}
	}
}

void	visualize_net()
{
	t_net		*net;
	t_hook		*params;
	t_list		*i;
	mlx_image_t	*img;

	net = *catch();
	if (net->display == false)
		return ;
	params = *vis();
	i = params->images;
	if (i)
	{
		img = i->content;
		if (img)
		{
			mlx_image_to_window(params->mlx, img, 0, 0);
			mlx_loop(params->mlx);
		}
	}
	else
		printf("no frames rendered\n");
}
