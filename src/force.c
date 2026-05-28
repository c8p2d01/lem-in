#include "../inc/lem_in.h"

# ifndef LINK_DIV
#  define LINK_DIV 42
# endif

void	random_force(t_graph *a)
{
	a->fpos.x += rand();
	a->fpos.y -= rand();
}

void	antigravity(t_graph *a)
{
	t_net	*net;
	t_list	*i;
	t_graph	*b;
	t_vec2d	p;
	float	min_dist;

	net = *catch();
	i = net->graph_nodes;
	min_dist = 0.4;
	while (i)
	{
		b = i->content;
		p.x = (b->x - a->x);
		p.y = (b->y - a->y);
		if (-min_dist < p.x && p.x < min_dist && -min_dist < p.y && p.y < min_dist)
		{
			b->fpos.x *= (0 - min_dist);
			b->fpos.y *= (0 - min_dist);
		}
		i = i->next;
	}
}

void	link_force(t_graph *a)
{
	t_list	*i;
	t_link	*link;
	t_graph *b;
	t_vec2d	dst_b;
	t_vec2d	sum;
	double	len;
	double	min_len;

	i = a->links;
	min_len = 0.7;
	sum = new_vec2d(0, 0);
	while (i)
	{
		link = i->content;
		b = ft_linked_to(a, link);
		dst_b = connect2d(new_vec2d(a->x, a->y), new_vec2d(b->x, b->y));
		len = veclen2d(&dst_b);
		if (len < min_len)
		{
			sum.x -= dst_b.x * (len / LINK_DIV);
			sum.y -= dst_b.y * (len / LINK_DIV);
		}
		else
		{
			sum.x += dst_b.x * (len / LINK_DIV);
			sum.y += dst_b.y * (len / LINK_DIV);
		}
		i = i->next;
	}
	a->fpos.x -= sum.x;
	a->fpos.y -= sum.y;
}

void	calculate_forces()
{
	t_net	*net;
	t_list	*i;
	t_graph	*a;
	t_hook	*h;

	net = *catch();
	i = net->graph_nodes;
	while (i)
	{
		a = i->content;
		if (!a->important)
		{
			if (a->x == a->y)
				random_force(a);
			link_force(a);
			//antigravity(a);
		}
		i = i->next;
	}
}

size_t	apply_forces()
{
	t_net	*net;
	t_list	*i;
	t_graph	*a;
	double	heatsum;
	double	c;

	net = *catch();
	i = net->graph_nodes;
	c = 0;
	while (i)
	{
		a = i->content;
		a->x += (0.00001 * a->fpos.x);
		a->y += (0.00001 * a->fpos.y);
		heatsum += veclen_2d(0.00001 * a->fpos.x, 0.00001 * a->fpos.y);
		i = i->next;
		c += 2;
	}
	determine_max_coordinates();
	corner_imprtant();
	return (heatsum / c);
}
