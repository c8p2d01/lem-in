#include "../inc/lem_in.h"

/**
 * @brief Free globe struct
 */
void	free_globe(globe *data)
{
	for (size_t i = 0; data->allNodes && data->allNodes[i] != NULL; ++i)
	{
		if (data->allNodes[i]->name)
			free(data->allNodes[i]->name);
		if (data->allNodes[i]->gates)
			free(data->allNodes[i]->gates);
		if (data->allNodes[i]->next_gates)
			free(data->allNodes[i]->next_gates);
		if (data->allNodes[i]->prev_gates)
			free(data->allNodes[i]->prev_gates);
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
 * @brief Delete all nodes that are not connected to the start/end node (not leveled)
 */
void	delete_useless_node(globe *data)
{
	for (size_t i = 0; data->allNodes[i]; ++i)
	{
		if (data->allNodes[i]->lvl == -1)
		{
			ft_g_del_node(data->allNodes[i]);
			ft_memmove(&data->allNodes[i], &data->allNodes[i + 1], sizeof(t_graph *) * (ft_array_size((void**)&data->allNodes[i + 1]) + 1));
			--i;
		}
	}
}

/**
 * @brief Remove link of nodes that are on the same level and have their own complete path
 */
void	unlink_same_level(globe *data)
{
	bool	found = false;
	for (size_t i = 0; data->allNodes[i]; ++i)
	{
		for (size_t j = 0; data->allNodes[i]->gates && data->allNodes[i]->gates[j]; ++j)
		{
			if (data->allNodes[i]->gates[j]->lvl == data->allNodes[i]->lvl)
			{
				found = false;
				for (size_t k = 0; data->allNodes[i]->next_gates && data->allNodes[i]->next_gates[k]; ++k)
				{
					if (data->allNodes[i]->next_gates[k] == data->allNodes[i]->gates[j])
					{
						found = true;
						break;
					}
				}
				for (size_t k = 0; !found && data->allNodes[i]->prev_gates && data->allNodes[i]->prev_gates[k]; ++k)
				{
					if (data->allNodes[i]->prev_gates[k] == data->allNodes[i]->gates[j])
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					ft_g_unlink(data->allNodes[i], data->allNodes[i]->gates[j]);
					--j;
				}
			}
		}
	}
	delete_deadend(data); // may not need this
}

/**
 * @brief Helper function to add node to array dynamically
 */
static void	add_node_to_array(t_graph ***array, t_graph *node)
{
	if (array == NULL)
		return ;
	if (*array == NULL)
	{
		*array = ft_calloc(2, sizeof(t_graph *));
		(*array)[0] = node;
		return ;
	}
	else
	{
		size_t size = ft_array_size((void **)(*array));
		*array = ft_realloc(*array, (size + 1) * sizeof(t_graph *), 1);
		(*array)[size] = node;
	}
}

/**
 * @brief Check if a node is deadend, meaning isn't not connected to any above or below node
 */
static bool	is_node_deadend(t_graph *node)
{
	if (node->gates == NULL)
		return (true);
	bool	has_next_level = false;
	bool	has_prev_level = false;
	bool	has_same_level = false;
	for (size_t i = 0; node->gates[i]; ++i)
	{
		if (node->gates[i]->lvl > node->lvl)
		{
			has_next_level = true;
		}
		else if (node->gates[i]->lvl < node->lvl)
		{
			has_prev_level = true;
		}
		else
		{
			has_same_level = true;
		}
	}
	if (!has_same_level && (!has_next_level || !has_prev_level))
		return (true);
	else if (has_same_level && !has_next_level && !has_prev_level)
		return (true);
	return (false);
}

/**
 * @brief Add directional link between two same level nodes
 * @note This also add to the other node next gates, not just current node prev gates
 */
static void	add_directional_same_level(t_graph *current_node, t_graph *other_node)
{
	for (size_t i = 0; current_node->next_gates && current_node->next_gates[i]; ++i)
	{
		if (current_node->next_gates[i] == other_node)
			return ;
	}
	for (size_t i = 0; current_node->prev_gates && current_node->prev_gates[i]; ++i)
	{
		if (current_node->prev_gates[i] == other_node)
			return ;
	}
	bool has_next_level = false;
	for (size_t i = 0; other_node->gates[i]; ++i)
	{
		if (other_node->gates[i]->lvl > other_node->lvl)
		{
			has_next_level = true;
		}
	}
	if (!has_next_level)
	{
		add_node_to_array(&current_node->prev_gates, other_node);
		add_node_to_array(&other_node->next_gates, current_node);
	}
}

/**
 * @brief Add directional link between nodes and remove link between nodes that are on same level and have their own complete path
 */
void	add_directional(globe *data)
{
	bool	has_next_level = false;
	bool	has_prev_level = false;
	for (size_t i = 0; data->allNodes[i]; ++i)
	{
		for (size_t j = 0; data->allNodes[i]->gates && data->allNodes[i]->gates[j]; ++j)
		{
			if (data->allNodes[i]->gates[j]->lvl > data->allNodes[i]->lvl)
			{
				add_node_to_array(&data->allNodes[i]->next_gates, data->allNodes[i]->gates[j]);
			}
			else if (data->allNodes[i]->gates[j]->lvl < data->allNodes[i]->lvl)
			{
				add_node_to_array(&data->allNodes[i]->prev_gates, data->allNodes[i]->gates[j]);
			}
			else if (!is_node_deadend(data->allNodes[i]->gates[j]))
			{
				add_directional_same_level(data->allNodes[i], data->allNodes[i]->gates[j]);
			}
		}
	}
}

/**
 * @brief Delete all the deadend nodes
 */
void	delete_deadend(globe *data)
{
	bool	has_next_level = false;
	bool	has_prev_level = false;
	bool	has_same_level = false;
	for (ssize_t i = 0; data->allNodes[i]; ++i)
	{
		if (data->allNodes[i] == data->end || data->allNodes[i] == data->start)
			continue ;
		if (is_node_deadend(data->allNodes[i]))
		{
			ft_g_del_node(data->allNodes[i]);
			ft_memmove(&data->allNodes[i], &data->allNodes[i + 1], sizeof(t_graph *) * (ft_array_size((void**)&data->allNodes[i + 1]) + 1));
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
 * @brief Check if this node and upstream has multiple output links
 */
static bool	is_upstream_multiple_output(globe *data, t_graph *node)
{
	while (node != data->start)
	{
		if (ft_array_size((void**)node->next_gates) > 1)
			return (true);
		assert(node->prev_gates != NULL && node->prev_gates[0] != NULL); // TODO: remove assert debug, there should be at least and only 1 input link
		node = node->prev_gates[0];
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
		while (ft_array_size((void**)data->allNodes[i]->prev_gates) > 1)
		{
			for (size_t j = 0; data->allNodes[i]->prev_gates && data->allNodes[i]->prev_gates[j]; ++j)
			{
				if (is_upstream_multiple_output(data, data->allNodes[i]->prev_gates[j]))
				{
					ft_g_unlink(data->allNodes[i], data->allNodes[i]->prev_gates[j]);
					delete_deadend(data);
					--i;
					assert(i > 0); // TODO: remove assert debug, first node after start should have only 1 prev gates start
					break;
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
		assert(node->next_gates != NULL && node->next_gates[0] != NULL); // TODO: remove assert debug, there should be at least and only 1 output node
		node = node->next_gates[0];
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
	size_t	array_size = ft_array_size((void*)data->allNodes);
	for (size_t i = array_size - 2; i > 1; --i)
	{
		if (ft_array_size((void**)data->allNodes[i]->next_gates) > 1)
		{
			min_path_len = SIZE_MAX;
			for (size_t j = 0; data->allNodes[i]->next_gates && data->allNodes[i]->next_gates[j]; ++j)
			{
				tmp_len = path_length(data, data->allNodes[i]->next_gates[j]);
				if (min_path_len > tmp_len)
				{
					min_path_len = tmp_len;
					path = data->allNodes[i]->next_gates[j];
				}
			}
			assert(path != NULL); // TODO: remove assert debug, there should be at least 1 path to the end
			for (size_t j = 0; data->allNodes[i]->next_gates && data->allNodes[i]->next_gates[j]; ++j)
			{
				if (data->allNodes[i]->next_gates[j] != path)
				{
					ft_g_unlink(data->allNodes[i], data->allNodes[i]->next_gates[j]);
					--j;
				}
			}
			delete_deadend(data);
			i = array_size - 2;
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
	for (size_t i = 0; node->prev_gates && node->prev_gates[i]; ++i)
	{
		if (node->prev_gates[i]->path_id == -1 && next_level > node->prev_gates[i]->lvl)
		{
			next_node = node->prev_gates[i];
			next_level = node->prev_gates[i]->lvl;
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
			for (size_t j = 0; node->next_gates && node->next_gates[j]; ++j)
			{
				if ((size_t)node->next_gates[j]->path_id == i || node->next_gates[j] == data->end)
				{
					node = node->next_gates[j];
					break;
				}
			}
		}
		printf("%s\n", data->end->name);
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
