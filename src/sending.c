#include "../inc/lem_in.h"

void	print_move(t_graph *a)
{
	int color;
	int rgb[3];
	t_net	*net;

	net = *catch();
	if (!net->display)
	{
		printf("L%i-%s ", a->ant, a->name);
		return ;
	}
	color = color_by_ant(a);
	rgb[0] = (color) % 256;
	rgb[1] = (color >> 8) % 256;
	rgb[2] = (color >> 16) % 256;
	printf("L\e[38;2;%i;%i;%im%i\e[0m-", rgb[2], rgb[1], rgb[0], a->ant);
	printf("%s ", a->name);
}

size_t	ant_step(t_path *path)
{
	t_list	*i;
	t_list	*p;
	t_graph	*graph;
	t_graph	*p_graph;
	size_t	stepped;

	i = ft_lstlast(path->path_nodes);
	if (i)
		i = i->prev;
	p = NULL;
	if (i)
		p = i->prev;
	stepped = 0;
	while (p)
	{
		graph = i->content;
		p_graph = p->content;
		graph->ant = p_graph->ant;
		if (p_graph->ant > 0)
		{
			print_move(graph);
			stepped++;
		}
		i = p;
		p = i->prev;
	}
	return (stepped);
}

void	calculate_packets()
{
	t_net			*net;
	size_t			packets;
	size_t			p;
	size_t			steps;
	size_t			p_steps;
	t_path			*path;

	net = *catch();
	packets = 0;
	while (packets < net->packets)
	{
		p = 0;
		path = net->paths;
		steps = (size_t)-1;
		while (p < net->n_paths)
		{
			p_steps = (net->paths + p)->packets + ft_lstsize((net->paths + p)->path_nodes);
			if (p_steps < steps)
			{
				steps = p_steps;
				path = net->paths + p;
			}
			p++;
		}
		path->packets++;
		packets++;
	}
}

size_t	send_packets()
{
	t_net			*net;
	size_t			p;
	t_path			*path;
	t_graph			*graph;
	size_t			stepped;
	size_t			remaining;
	size_t			nodes_used;
	size_t			longest_used;
	size_t			path_length;
	static size_t	ant = 1;
	static size_t	lines = 1;

	net = *catch();
	p = 0;
	stepped = 0;
	nodes_used = 0;
	longest_used = 0;
	while (p < net->n_paths)
	{
		path = net->paths + p;
		stepped += ant_step(path);
		graph = path->path_nodes->next->content;
		if (remaining && path->packets)
		{
			path->packets--;
			ant++;
			stepped++;
			graph->ant = ant;
			print_move(graph);
		}
		else
			graph->ant = -42;
		p++;
	}
	printf("\n");
	if (!stepped)
		printf("step count : %lu\n", lines);
	lines ++;
	return (stepped);
}
