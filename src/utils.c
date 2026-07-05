#include "../inc/lem_in.h"

void	print_path(t_path *path)
{
	t_list	*i;
	t_graph	*graph;
	int color;
	int rgb[3];

	i = path->path_nodes;
	while (i)
	{
		graph = i->content;
		color = color_by_ant(graph);
		rgb[0] = (color) % 256;
		rgb[1] = (color >> 8) % 256;
		rgb[2] = (color >> 16) % 256;
		printf("\e[38;2;%i;%i;%im%s\e[0m --- ", rgb[0], rgb[1], rgb[2], graph->name);
		i = i->next;
	}
	printf("\n");
}

void	print_paths()
{
	t_net	*net;
	size_t	i;
	t_path	*path;

	net = *catch();
	i = 0;
	while (i < net->n_paths)
	{
		printf("path %i\tlen %i\n", i, ft_lstsize((net->paths + i)->path_nodes));
		path = net->paths + i;
		print_path(path);
		i++;
	}
}

