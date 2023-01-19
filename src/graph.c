#include "../inc/lem_in.h"

/**
 * @brief Free globe struct
 */
void	freeGlobe(globe *data)
{
	for (size_t i = 0; data->allNodes && data->allNodes[i] != NULL; ++i)
	{
		if (data->allNodes[i]->name)
			free(data->allNodes[i]->name);
		if (data->allNodes[i]->gates)
			free(data->allNodes[i]->gates);
		free(data->allNodes[i]);
	}
	if (data->allNodes)
		free(data->allNodes);
}

/**
 * @brief BFS to assign level to each node
 * Start node is level 0, end node is level SSIZE_MAX
 */
void	add_level(globe *data)
{
	t_list	*queue = ft_lstnew(data->start);
	t_list	*queue_head = queue;
	ssize_t	level = 0;
	size_t	count1 = 1;
	size_t	count2 = 0;
	while (queue)
	{
		if (((t_graph *)(queue->content))->lvl == -1)
		{
			((t_graph *)(queue->content))->lvl = level;
		}
		for (size_t i = 0; (t_graph *)(queue->content) != data->end && ((t_graph *)(queue->content))->gates[i]; ++i)
		{
			if (((t_graph *)(queue->content))->gates[i]->lvl == -1)
			{
				ft_lstadd_back(&queue, ft_lstnew(((t_graph *)(queue->content))->gates[i]));
				count2++;
			}
		}
		if (--count1 == 0)
		{
			level++;
			count1 = count2;
			count2 = 0;
		}
		queue = queue->next;
	}
	data->end->lvl = SSIZE_MAX;
	ft_lstclear(&queue_head, NULL);
}

/**
 * @brief Delete all nodes that are not connected to the start/end node
 */
void	delete_useless_node(globe *data)
{
	for (size_t i = 0; data->allNodes[i]; ++i)
	{
		if (data->allNodes[i]->lvl == -1)
		{
			ft_g_del_node(data->allNodes[i]);
			for (size_t j = i; data->allNodes[j]; ++j)
			{
				data->allNodes[j] = data->allNodes[j + 1];
			}
			--i;
		}
	}
}

/**
 * @brief Remove link of nodes that are on the same level and have their own complete path
 */
void	unlink_same_level(globe *data)
{
	for (size_t i = 0; data->allNodes[i]; ++i)
	{
		for (size_t j = 0; data->allNodes[i]->gates && data->allNodes[i]->gates[j]; ++j)
		{
			if (data->allNodes[i]->lvl == data->allNodes[i]->gates[j]->lvl)
			{
				ft_g_unlink(data->allNodes[i], data->allNodes[i]->gates[j]);
				--j;
			}
		}
	}
}

/**
 * @brief Delete all the deadend nodes that isn't connected to any next or previous level node
 */
void	delete_deadend(globe *data)
{
	bool	has_next_level = false;
	bool	has_prev_level = false;
	for (ssize_t i = 1; data->allNodes[i]; ++i)
	{
		if (data->allNodes[i] == data->end || data->allNodes[i] == data->start)
			continue ;
		has_next_level = false;
		has_prev_level = false;
		for (size_t j = 0; data->allNodes[i]->gates && data->allNodes[i]->gates[j]; ++j)
		{
			if (data->allNodes[i]->gates[j]->lvl > data->allNodes[i]->lvl)
			{
				has_next_level = true;
			}
			else if (data->allNodes[i]->gates[j]->lvl < data->allNodes[i]->lvl)
			{
				has_prev_level = true;
			}
		}
		if (data->allNodes[i]->gates == NULL || !has_next_level || !has_prev_level)
		{
			ft_g_del_node(data->allNodes[i]);
			for (size_t k = i; data->allNodes[k]; ++k)
			{
				data->allNodes[k] = data->allNodes[k + 1];
			}
			i = -1;
		}
	}
}

/**
 * @brief Sort nodes and their connected nodes by level
 */
void	sort_level(globe *data)
{
	t_graph	**sorted_nodes;

	sorted_nodes = ft_calloc(ft_array_size((void*)(data->allNodes)) + 1, sizeof(t_graph *));
	for (ssize_t current_level = -1; ft_array_size((void*)sorted_nodes) < ft_array_size((void*)(data->allNodes)); ++current_level)
	{
		for (size_t i = 0; data->allNodes[i]; ++i)
		{
			if (data->allNodes[i]->lvl == current_level)
			{
				sorted_nodes[ft_array_size((void*)sorted_nodes)] = data->allNodes[i];
			}
		}
		if (ft_array_size((void*)sorted_nodes) == ft_array_size((void*)(data->allNodes)) - 1)
		{
			current_level = SSIZE_MAX - 1;
		}
	}
	free(data->allNodes);
	data->allNodes = sorted_nodes;
}

/**
 * @brief Count input link of this node
 */
static size_t	count_input_link(t_graph *node)
{
	size_t	count = 0;

	for (size_t i = 0; node->gates && node->gates[i]; ++i)
	{
		if (node->gates[i]->lvl < node->lvl)
			++count;
	}
	return (count);
}

/**
 * @brief Count output link of this node
 */
static size_t	count_output_link(t_graph *node)
{
	size_t	count = 0;

	for (size_t i = 0; node->gates && node->gates[i]; ++i)
	{
		if (node->gates[i]->lvl > node->lvl)
			++count;
	}
	return (count);
}

/**
 * @brief Get the first parent input node
 */
static t_graph*	get_first_input_node(t_graph *node)
{
	for (size_t i = 0; node->gates && node->gates[i]; ++i)
	{
		if (node->gates[i]->lvl < node->lvl)
			return (node->gates[i]);
	}
	return (NULL);
}

/**
 * @brief Get the first child onput node
 */
static t_graph*	get_first_onput_node(t_graph *node)
{
	for (size_t i = 0; node->gates && node->gates[i]; ++i)
	{
		if (node->gates[i]->lvl > node->lvl)
			return (node->gates[i]);
	}
	return (NULL);
}

/**
 * @brief Check if this node and upstream has multiple output links
 */
static bool	is_upstream_multiple_output(globe *data, t_graph *node)
{
	while (node != data->start)
	{
		if (count_output_link(node) > 1)
			return (true);
		assert(get_first_input_node(node) != NULL); // TODO: remove assert debug, there should be at least and only 1 input link
		node = get_first_input_node(node);
	}
	return (false);
}

/**
 * @brief Unlink all nodes that have more than 1 input link
 */
void	remove_input_links(globe *data)
{
	for (size_t i = 1; data->allNodes[i + 1]; ++i)
	{
		while (count_input_link(data->allNodes[i]) > 1)
		{
			for (size_t j = 0; data->allNodes[i]->gates && data->allNodes[i]->gates[j]; ++j)
			{
				if (data->allNodes[i]->gates[j]->lvl < data->allNodes[i]->lvl && is_upstream_multiple_output(data, data->allNodes[i]->gates[j]))
				{
					ft_g_unlink(data->allNodes[i], data->allNodes[i]->gates[j]);
					delete_deadend(data);
					--j;
				}
			}
		}
	}
}

/**
 * @brief Path length from current node to end node
 */
static size_t	path_length(globe *data, t_graph *node)
{
	size_t	length = 0;

	while (node != data->end)
	{
		assert(get_first_onput_node(node) != NULL); // TODO: remove assert debug, there should be at least and only 1 output node
		node = get_first_onput_node(node);
		++length;
	}
	return (length);
}

/**
 * @brief Unlink all nodes that have more than 1 output link
 */
void	remove_output_links(globe *data)
{
	size_t	min_path_len = SIZE_MAX;
	size_t	tmp_len = 0;
	t_graph	*path = NULL;
	for (size_t i = ft_array_size((void*)data->allNodes) - 2; i > 1; --i)
	{
		while (count_output_link(data->allNodes[i]) > 1)
		{
			min_path_len = SIZE_MAX;
			for (size_t j = 0; data->allNodes[i]->gates && data->allNodes[i]->gates[j]; ++j)
			{
				if (data->allNodes[i]->gates[j]->lvl > data->allNodes[i]->lvl)
				{
					tmp_len = path_length(data, data->allNodes[i]->gates[j]);
					if (min_path_len > tmp_len)
					{
						min_path_len = tmp_len;
						path = data->allNodes[i]->gates[j];
					}
				}
			}
			assert(path != NULL); // TODO: remove assert debug, there should be at least 1 path to the end
			for (size_t j = 0; data->allNodes[i]->gates && data->allNodes[i]->gates[j]; ++j)
			{
				if (data->allNodes[i]->gates[j]->lvl > data->allNodes[i]->lvl && data->allNodes[i]->gates[j] != path)
				{
					ft_g_unlink(data->allNodes[i], data->allNodes[i]->gates[j]);
					delete_deadend(data);
					--j;
				}
			}
		}
	}
}

/**
 * @brief Find shortest path that isn't already taken based on level recursively
 */
static bool	find_shortest_path(globe *data, t_graph	*node)
{
	if (node == NULL)
	{
		return (false);
	}
	else if (node == data->start)
	{
		return (true);
	}
	t_graph	*next_node = NULL;
	ssize_t	next_level = SSIZE_MAX;
	node->path_id = data->nPaths;
	for (size_t i = 0; node->gates && node->gates[i]; ++i)
	{
		if (node->gates[i]->path_id == -1 && node->gates[i]->lvl < node->lvl && next_level > node->gates[i]->lvl)
		{
			next_node = node->gates[i];
			next_level = node->gates[i]->lvl;
		}
	}
	if (!find_shortest_path(data, next_node))
	{
		node->path_id = -1;
		return (false);
	}
	return (true);
}

/**
 * @brief Find all shortest paths from start to end
 */
void	find_all_shortest_paths(globe *data)
{
	while (find_shortest_path(data, data->end))
	{
		++data->nPaths;
	}
	data->end->path_id = -1;
}

/**
 * @brief Print all paths
 */
void	print_paths(globe *data)
{
	t_graph	*node = data->start;
	printf("Number of paths: %zu\n", data->nPaths);
	for (size_t i = 0; i < data->nPaths; ++i)
	{
		node = data->start;
		printf("Path %zu: ", i);
		while (node != data->end)
		{
			printf("%s -> ", node->name);
			for (size_t j = 0; node->gates && node->gates[j]; ++j)
			{
				if ((node->gates[j]->lvl > node->lvl && (size_t)node->gates[j]->path_id == i) || node->gates[j] == data->end)
				{
					node = node->gates[j];
					break ;
				}
			}
		}
		printf("\n");
	}
}

// /**
//  * @brief free a node and remove its traces from tho nodes it was connected to
//  */
// void	ft_gErase(gNode *node)
// {
// 	size_t i = 0;
// 	while (node->gates && node->gates[i])
// 	{
// 		size_t	s = arraySize((void **)node->gates[i]->gates);
// 		gNode	**new = ft_calloc(s, sizeof(gNode*));
// 		size_t	n = 0;
// 		size_t	o = 0;
// 		while (n < s)
// 		{
// 			if (node->gates[i]->gates[n + o] == node)
// 				o++;
// 			new[n] = node->gates[i]->gates[n + o];
// 			n++;
// 		}
// 		i++;
// 	}
// 	free(node->gates);
// 	free(node->name);
// 	free(node);
// }

// void	ft_gClean(gNode *node)
// {
// 	size_t amount = 0;
// 	while (node->gates[amount] != NULL)
// 		amount++;
// 	gNode **comp = ft_calloc((amount + 1), sizeof(gNode*));
// 	for (size_t i = 0; i < amount; i++)
// 	{
// 		int a = 0;
// 		while (comp[a] != NULL && comp[a] != node->gates[i])
// 			a++;
// 		if (comp[a])
// 			continue;
// 		while (comp[a] != NULL)
// 			a++;
// 		comp[a] = node->gates[i];
// 	}
// }
