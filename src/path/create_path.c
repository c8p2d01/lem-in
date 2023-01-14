#include "../../inc/lem_in.h"

int connection(t_graph* node, size_t size)
{
	size_t i = 0; 
	while (node->gates[i]->lvl < node->lvl && i < size)
		i ++;
	return (i);
}

int check_links_d(t_graph* node, size_t p_connect, t_graph* previous)
{
	size_t size = ft_array_size((void **)node->gates);
	size_t connect = size;
	size_t connect_l = connection(node, size);

	if (connect_l > 1)
}

int check_path(t_graph* node, size_t p_connect, t_graph* previous)
{
	size_t size = ft_array_size((void **)node->gates);
	size_t connect = size;

	for (size_t i = 0;connect > 1 && i < size; i ++)
	{
		if (node->gates[i]->lvl < node->lvl)
		{
			if (node->gates[i]->lvl == 0)
				continue;
			printf("This node [%s] has a lesser connection to [%s]", node->name, node->gates[i]->name);// DEBUG
		}
		if (node->gates[i]->lvl == node->lvl)
		{
			ft_g_unlink(node, node->gates[i]);
			i --;
			connect --;
			continue;
		}
		if (node->gates[i]->lvl > node->lvl && i < size - 1)
		{
			check_links_d(node->gates[i], size - 1 - i, node);
		}
	}
}