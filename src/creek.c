#include "../inc/lem_in.h"

void	mapper(t_path *river)
{
	int i = 0;

	if (!river)
		return ;
	printf("riverlen %zu\n", river->len);
	while(river && river->path && river->path[i])
	{
		printf("\tnode '%s'\n", river->path[i]->name);
		i++;
	}
}

t_path	**cartograph(globe *data)
{
	int maxFlow = ft_flow_link_size(data->end);
	int i = 0;
	int m = 0;

	t_path	**map = ft_calloc((maxFlow + 1), sizeof(t_path *));
	for (t_link *link = data->end->links[i];map && link; )
	{
		while ( data->end->links[i] && !ft_active_link(link))
			link = data->end->links[++i];
		map[m++] = river(link, data->end, data->start);
		link = data->end->links[++i];
			//mapper(map[m - 1]);
	}
	return(map);
}

t_path	*river(t_link *flow, t_room *spring, t_room *estuary)
{
	size_t	len = 1;
	int		n = 0;

	for (t_room *node = ft_otherside(flow, spring);node && node != estuary; )
	{
		
		n = 0;
		while (node->links && node->links[n])
		{
			if (ft_flow(node->links[n], node) == 1)
			{
				len++;
				node = ft_otherside(node->links[n], node);
				n = 0;
			}
			n++;
		}
	}

	t_path	*river = malloc(sizeof(t_path));
	river->path = ft_calloc((len + 1), sizeof(t_room *));
	if (!river || !river->path)
		return(NULL);
	river->len = len;

	len = 0;
	river->path[len] = spring;
	for (t_room *node = ft_otherside(flow, spring); node && node != estuary; )
	{
		n = 0;
		while (node->links && node->links[n])
		{
			if (ft_flow(node->links[n], node) == 1)
			{
				len++;
				node = ft_otherside(node->links[n], node);
				river->path[len] = node;
			}
			n++;
		}
	}
	return (river);
}