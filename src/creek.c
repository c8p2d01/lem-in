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

void path_sort(globe *data)
{
	int max = ft_flow_link_size(data->end);
	t_path **paths = calloc(max + 1, sizeof(t_path *));
	int x = 0;
	int i = 0;
	t_path *tmp = NULL;
	while (data->paths[i])
	{
		tmp = data->paths[i];
		x = i;
		while (x > 0)
		{
			if (tmp->len >= paths[x - 1]->len)
				break ;
			paths[x] = paths[x - 1];
			x --;
		}
		paths[x] = tmp;
		i ++;
	}
	free(data->paths);
	data->paths = paths;
}

t_path	**cartograph(globe *data)
{
	int maxFlow = ft_flow_link_size(data->end);
	int i = 0;
	int m = 0;

	t_path	**map = ft_calloc((maxFlow + 1), sizeof(t_path *));
	for (t_link *link = data->start->links[i];map && link && m < maxFlow; )
	{
		while (link && !ft_active_link(link) && ft_flow(link, data->start) != -1)
			link = data->start->links[++i];
		map[m++] = river(link, data->start, data->end);
		link = data->start->links[++i];
			mapper(map[m - 1]);
	}
	return(map);
}

t_path	*river(t_link *flow, t_room *spring, t_room *estuary)
{
	size_t	len = 1;
	int		n = 0;
	int		flw;

	for (t_room *node = ft_otherside(flow, spring);node && node != estuary; )
	{
		
		n = 0;
		while (node->links && node->links[n])
		{
			flw = ft_flow(node->links[n], node);
			if (flw == -1)
			{
				len++;
				node = ft_otherside(node->links[n], node);
				n = 0;
			}
			else
				n++;
		}
		if (node == estuary)
		{
			len++;
			break;
		}
	}

	t_path	*river = malloc(sizeof(t_path));
	river->path = ft_calloc((len + 1), sizeof(t_room *));
	if (!river || !river->path)
		return(NULL);
	river->len = len;
	river->ant = -1;

	len = 0;
	river->path[len] = spring;
	for (t_room *node = ft_otherside(flow, spring); node && node != estuary; )
	{
		n = 0;
		while (node->links && node->links[n])
		{
			flw = ft_flow(node->links[n], node);
			if (flw == -1)
			{
				len++;
				river->path[len] = node;
				node = ft_otherside(node->links[n], node);
				n = 0;
			}
			else
				n++;
		}
		if (node == estuary)
		{
			len++;
			river->path[len] = node;
			break;
		}
	}
	return (river);
}