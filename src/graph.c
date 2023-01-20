#include "../inc/lem_in.h"

/**
 * @brief Free globe struct
 */
void	free_globe(globe *data)
{
	for (size_t i = 0; data->graph && data->graph[i] != NULL; ++i)
	{
		if (data->graph[i]->name)
			free(data->graph[i]->name);
		if (data->graph[i]->links)
			free(data->graph[i]->links);
		free(data->graph[i]);
	}
	for (size_t i = 0; data->linkedlist && data->linkedlist[i] != NULL; ++i)
	{
		free(data->linkedlist[i]);
	}
	if (data->graph)
		free(data->graph);
	if (data->linkedlist)
		free(data->linkedlist);
}

/**
 * @brief Remove all deadend and useless nodes
 */
void	remove_deadend(globe *data)
{
	for (size_t i = 0; data->graph[i]; ++i)
	{
		if (ft_active_link_size(data->graph[i]) < 2)
		{
			ft_g_del_node(data->graph[i]);
			ft_memmove(&data->graph[i], &data->graph[i + 1], sizeof(t_room *) * (ft_array_size((void **)&data->graph[i + 1]) + 1));
			i = -1;
		}
	}
}
