#include "../inc/lem_in.h"
#include "../MLX42/include/MLX42/MLX42.h"

#ifndef WDTH
# define WDTH 800
#endif

#ifndef HGHT
# define HGHT 800
#endif

#ifndef FRAME
# define FRAME 10
#endif

void	keyhook(void *param)
{
	t_hook			*params;
	
	params = (t_hook*)param;
	if (mlx_is_key_down(params->mlx, MLX_KEY_ESCAPE))
		interrupt("");
	else if (params->press == false && mlx_is_key_down(params->mlx, MLX_KEY_RIGHT))
	{
		params->press = true;
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
	t_hook	*params;
	t_list	*i;
	t_graph	*graph;

	net = *catch();
	params = *vis();
	i = net->graph_nodes;
	while (i)
	{
		graph = (t_graph *)i->content;
		if (graph->x < params->min_x)
			params->min_x = graph->x;
		if (graph->y < params->min_y)
			params->min_y = graph->y;
		if (graph->x > params->max_x)
			params->max_x = graph->x;
		if (graph->y > params->max_y)
			params->max_y = graph->y;
		i = i->next;
	}
}

int	create_rgbt(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_links(t_hook *params, mlx_image_t *img)
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
		x = (int)((float)((graph->x - params->min_x)) / (float)((params->max_x - params->min_x)) * (WDTH - 2 * FRAME)) + FRAME;
		y = (int)((float)((graph->y - params->min_y)) / (float)((params->max_y - params->min_y)) * (HGHT - 2 * FRAME)) + FRAME;
		graph = link->to;
		x2 = (int)((float)((graph->x - params->min_x)) / (float)((params->max_x - params->min_x)) * (WDTH - 2 * FRAME)) + FRAME;
		y2 = (int)((float)((graph->y - params->min_y)) / (float)((params->max_y - params->min_y)) * (HGHT - 2 * FRAME)) + FRAME;

		if (link->flow != 0)
		{
			color = create_rgbt(16, 16, 224, 255);
			if (!link->active)
				color = create_rgbt(196, 32, 196, 255);
		}
		else
		{
			color = create_rgbt(128, 128, 128, 255);
			if (!link->active)
				color = create_rgbt(16, 16, 16, 255);
		}
		line(img, x, y, x2, y2, color);
		i = i->next;
	}
}

/** 
 * color nodes by which path the are assinged to
 * if run before pathing is done it colors by net
 */
int	color_by_path(t_graph *a)
{
	t_net		*net;
	float		max;
	float		fraction;
	float		dist;

	net = *catch();
	max = net->n_paths;
	dist = (float)a->path;
	if (dist < 0)
		dist += max;
	fraction = dist / (float)(max);
	if (fraction < 0)
		fraction += 1;
	int color = create_multi_gradient(fraction, 2, 0,255,255, 0,0,255, 255,0,255, 255,0,0, 255,255,0, 0,255,0);
	return (color << 8 | 255);
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
	return (color << 8 | 255);
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
	max = net->packets;
	fraction = (float)a->ant / (float)(max);
	if (fraction < 0)
		fraction += 1;
	int color = create_multi_gradient(fraction, 6, 255,0,0, 255,255,0, 0,255,0, 0,255,255, 0,0,255, 255,0,255);
	return (color << 8 | 255);
}

void	draw_nodes(t_hook *params, int(f)(t_graph *), mlx_image_t *img)
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
		x = (int)(((graph->x - params->min_x) / (params->max_x - params->min_x)) * (WDTH - 2 * FRAME)) + FRAME;
		y = (int)(((graph->y - params->min_y) / (params->max_y - params->min_y)) * (HGHT - 2 * FRAME)) + FRAME;
		square(img, x, y, FRAME, f(graph));
		i = i->next;
	}
}

void	corner_imprtant()
{
	t_net		*net;
	t_hook		*params;

	net = *catch();
	params = *vis();
	net->end->x = params->max_x - FRAME;
	net->end->y = params->max_y - FRAME;
	net->start->x = params->min_x + FRAME;
	net->start->y = params->min_y + FRAME;
}

void	plot_graph(int(f)(t_graph *))
{
	t_hook		*params;
	mlx_image_t	*img;
	t_list		*new;

	determine_max_coordinates();
	corner_imprtant();
	if ((t_net *)(*catch())->visualize == false)
		return ;
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

void	visualize_net()
{
	t_hook		*params;
	t_list		*i;
	mlx_image_t	*img;

	if ((t_net *)(*catch())->visualize == false)
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
	else
		printf("HEH\n");
	}
	else
		printf("HEH\n");
}
