#include "../inc/lem_in.h"
#include "../MLX42/include/MLX42/MLX42.h"

#ifndef WDTH
# define WDTH 800
#endif

#ifndef HGHT
# define HGHT 400
#endif

#ifndef FRAME
# define FRAME 10
#endif

typedef struct s_hook
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_hook;

void	keyhook(void *param)
{
	t_hook *params;
	
	params = (t_hook*)param;
	if (mlx_is_key_down(params->mlx, MLX_KEY_ESCAPE))
		interrupt("");
}

void	square(mlx_image_t *img, size_t x, size_t y, size_t len, int color)
{
	size_t	x0;
	size_t	y0;
	size_t	x1;
	size_t	y1;

	x0 = x - len / 2;
	x1 = x + len / 2;
	while (x0 < WDTH && x0 < x1)
	{
		y0 = y - len / 2;
		y1 = y + len / 2;
		while (y0 < HGHT && y0 < y1)
		{
			mlx_put_pixel(img, x0, y0, color);
			y0++;
		}
		x0++;
	}
}

void	line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
	int e2;

	while (1)
	{
		// 1. Guard against drawing outside your image boundary limits
		if (x0 >= 0 && x0 < WDTH && y0 >= 0 && y0 < HGHT) // Assuming HGHT is defined
			mlx_put_pixel(img, x0, y0, color);

		// 2. Break condition when the end of the line is reached
		if (x0 == x1 && y0 == y1)
			break ;

		// 3. Calculate the step adjustments using integer error margins
		e2 = 2 * error;
		if (e2 >= dy)
		{
			error += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			error += dx;
			y0 += sy;
		}
	}
}

void	determine_max_coordinates()
{
	t_net	*net;
	t_list	*i;
	t_graph	*graph;

	net = *catch();
	net->min_x = 2147483647;
	net->min_y = 2147483647;
	net->max_x = -2147483648;
	net->max_y = -2147483648;
	i = net->graph_nodes;
	while (i)
	{
		graph = (t_graph *)i->content;
		if (graph->x < net->min_x)
			net->min_x = graph->x;
		if (graph->y < net->min_y)
			net->min_y = graph->y;
		if (graph->x > net->max_x)
			net->max_x = graph->x;
		if (graph->y > net->max_y)
			net->max_y = graph->y;
		i = i->next;
	}
}

int	create_rgbt(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_links(t_hook *params)
{
	t_net		*net;
	t_list		*i;
	t_link		*link;
	t_graph		*graph;
	int			x;
	int			y;
	int			x2;
	int			y2;
	int			color;

	net = *catch();
	i = net->graph_links;
	while (i)
	{
		link = (t_link *)i->content;
		graph = link->from;
		x = (int)((float)((graph->x - net->min_x)) / (float)((net->max_x - net->min_x)) * (WDTH - 2 * FRAME)) + FRAME;
		y = (int)((float)((graph->y - net->min_y)) / (float)((net->max_y - net->min_y)) * (HGHT - 2 * FRAME)) + FRAME;
		graph = link->to;
		x2 = (int)((float)((graph->x - net->min_x)) / (float)((net->max_x - net->min_x)) * (WDTH - 2 * FRAME)) + FRAME;
		y2 = (int)((float)((graph->y - net->min_y)) / (float)((net->max_y - net->min_y)) * (HGHT - 2 * FRAME)) + FRAME;

		color = create_rgbt(128, 128, 128, link->active ? 255 : 64);
		if (link->flow != 0)
			color = create_rgbt(32, 32, 246, link->active ? 255 : 64);
		line(params->img, x, y, x2, y2, color);
		i = i->next;
	}
}

int	color_by_distance(t_graph *a)
{
	t_net		*net;
	size_t		max;
	float		fraction;

	net = *catch();
	max = net->end->dist - net->start->dist;
	fraction = (float)a->dist / (float)(max);
	if (fraction < 0)
		fraction += 1;
	int color = create_multi_gradient(fraction, 6, 255,0,0, 255,255,0, 0,255,0, 0,255,255, 0,0,255, 255,0,255);
	return (color << 8 | 255);
}

void	draw_nodes(t_hook *params, int(f)(t_graph *))
{
	t_net		*net;
	t_list		*i;
	t_graph		*graph;
	int			x;
	int			y;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		graph = (t_graph *)i->content;
		x = (int)((float)((graph->x - net->min_x)) / (float)((net->max_x - net->min_x)) * (WDTH - 2 * FRAME)) + FRAME;
		y = (int)((float)((graph->y - net->min_y)) / (float)((net->max_y - net->min_y)) * (HGHT - 2 * FRAME)) + FRAME;
		square(params->img, x, y, FRAME, f(graph));
		i = i->next;
	}
}

void	visualize_net()
{
	t_hook		params;
	t_net		*net;
	t_list		*i;
	t_graph		*graph;
	t_link		*link;
	int			x;
	int			y;
	int			x2;
	int			y2;

	params.mlx = mlx_init(WDTH, HGHT, "Graph-network", true);
	params.img = mlx_new_image(params.mlx, WDTH, HGHT);
	mlx_image_to_window(params.mlx, params.img, 0, 0);
	net = *catch();
	determine_max_coordinates();
	draw_links(&params);
	draw_nodes(&params, color_by_distance);

	mlx_loop_hook(params.mlx, keyhook, &params);
	mlx_loop(params.mlx);
}