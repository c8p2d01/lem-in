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
	if (data->graph)
		free(data->graph);
}

///**
// * @brief Remove node that isn't connected to anywhere (not leveled)
// */
//void	remove_useless(globe *data)
//{
//	for (size_t i = 0; data->graph[i]; ++i)
//	{
//		if (data->graph[i]->lvl == -1)
//		{
//			ft_g_del_node(data->graph[i]); // TODO: no del node func
//			ft_memmove(&data->graph[i], &data->graph[i + 1], sizeof(t_room *) * (ft_array_size((void **)&data->graph[i + 1]) + 1));
//			--i;
//		}
//	}
//}

///**
// * @brief Remove all deadend nodes
// */
//void	remove_deadend(globe *data)
//{
//	for (size_t i = 0; data->graph[i]; ++i)
//	{
//		if (ft_array_size((void **)data->graph[i]->links) == 1)
//		{
//			ft_g_del_node(data->graph[i]); // TODO: no del node func
//			ft_memmove(&data->graph[i], &data->graph[i + 1], sizeof(t_room *) * (ft_array_size((void **)&data->graph[i + 1]) + 1));
//			i = -1;
//		}
//	}
//}

/**
 * @brief Print all nodes and its gates
 * @note Debug
 */
void	print_nodes(t_room **node)
{
	for (size_t i = 0; node[i]; ++i)
	{
		printf("node '%s'\tlevel %li\n", node[i]->name, node[i]->lvl);
		for (size_t j = 0; node[i]->links && node[i]->links[j]; ++j)
		{
			if (node[i]->links[j]->vroom == node[i])
				printf("\t link to '%s'\n", node[i]->links[j]->moorv->name);
			else
				printf("\t link to '%s'\n", node[i]->links[j]->vroom->name);
		}
	}
}

// /**
//  * @brief free a node and remove its traces from tho nodes it was connected to
//  */
// void	ft_gErase(gNode *node)
// {
// 	size_t i = 0;
// 	while (node->links && node->links[i])
// 	{
// 		size_t	s = arraySize((void **)node->links[i]->links);
// 		gNode	**new = ft_calloc(s, sizeof(gNode*));
// 		size_t	n = 0;
// 		size_t	o = 0;
// 		while (n < s)
// 		{
// 			if (node->links[i]->links[n + o] == node)
// 				o++;
// 			new[n] = node->links[i]->links[n + o];
// 			n++;
// 		}
// 		i++;
// 	}
// 	free(node->links);
// 	free(node->name);
// 	free(node);
// }

// void	ft_gClean(gNode *node)
// {
// 	size_t amount = 0;
// 	while (node->links[amount] != NULL)
// 		amount++;
// 	gNode **comp = ft_calloc((amount + 1), sizeof(gNode*));
// 	for (size_t i = 0; i < amount; i++)
// 	{
// 		int a = 0;
// 		while (comp[a] != NULL && comp[a] != node->links[i])
// 			a++;
// 		if (comp[a])
// 			continue;
// 		while (comp[a] != NULL)
// 			a++;
// 		comp[a] = node->links[i];
// 	}
// }
