#include "../inc/lem_in.h"

int max_flow(t_room *start)
{

	int max_flow = 0;
	for (int i = 0; start->links[i]; i ++)
	{
		if (ft_flow(start->links[i], start) == -1)
			max_flow ++;
	}
	return (max_flow);
}
void path_sort(globe *data)
{
	int max = max_flow(data->start);
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