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

void	level(globe *data)
{
	t_list	*q = ft_lstnew(data->start);
	t_list	*t = q;
	size_t	level = 0;
	size_t	count1 = 1;
	size_t	count2 = 0;
	while(q)
	{
		if (((t_graph *)(q->content))->lvl < 0)
			((t_graph *)(q->content))->lvl = level;
		for(int i = 0; ((t_graph *)(q->content))->gates[i] ; i++)
		{
			if (((t_graph *)(q->content))->gates[i]->lvl < 0)
			{
				ft_lstadd_back(&q, ft_lstnew(((t_graph *)(q->content))->gates[i]));
				count2++;
			}
		}
		if (--count1 == 0)
		{
			level++;
			count1 = count2;
			count2 = 0;
		}
		q = q->next;
	}
	ft_lstclear(&t, NULL);
}

void	level_sort(globe *data)
{
	t_graph	**s;
	t_graph	**r;
	ssize_t	l;

	s = ft_calloc(arraySize((void **)data->allNodes) + 1, sizeof(t_graph *));
	for (size_t i = 0; i < arraySize((void **)data->allNodes); i++)
	{
		if ((data->allNodes[i])->lvl < 0)
		{
			ft_g_del_node(data->allNodes[i]);
		}
		else
		{
			s[ft_array_size((void **)s)] = data->allNodes[i];
		}
	}
	r = ft_calloc(arraySize((void **)s) + 1, sizeof(t_graph *));
	l = 0;
	while (arraySize((void **)r) < arraySize((void **)s))
	{
		for (int i = 0; s[i]; i++)
		{
			if (s[i]->lvl == l)
				r[ft_array_size((void **)r)] = s[i];
		}
		l++;
	}
	free(data->allNodes);
	free(s);
	data->allNodes = r;
}

/**
 * @brief Find one shortest path without path already taken
 * TODO: probably make this into recursive so doesn't to backtrack in case no possible next_node
 */
static bool	find_shortest_path(globe *data)
{
	t_graph *node = data->end;
	t_graph *next_node = NULL;
	size_t i = 0;
	size_t next_lvl;

	while (node && node != data->start)
	{
		next_node = NULL;
		next_lvl = SIZE_MAX;
		node->path_id = data->nPaths;

		for (i = 0; node->gates[i]; ++i)
		{
			if (next_lvl >= (size_t)node->gates[i]->lvl && node->gates[i]->path_id == -1)
			{
				next_lvl = node->gates[i]->lvl;
				next_node = node->gates[i];
			}
		}

		if (next_node == NULL)
		{
			while (node && node != data->end)
			{
				next_node = NULL;
				node->path_id = -1;

				for (i = 0; node->gates[i]; ++i)
				{
					if ((size_t)node->gates[i]->path_id == data->nPaths)
					{
						next_node = node->gates[i];
						break;
					}
				}

				if (next_node == NULL)
					break;
				node = next_node;
			}
			return false;
		}
		node = next_node;
	}

	return true;
}

/**
 * @brief Find all shortest paths but not maximum parallel
 * @note Start and end node path id are always -1 (or maybe we should set it to something else)
 */
void	find_all_shortest_paths(globe *data)
{
	while (find_shortest_path(data))
		data->nPaths++;
	data->end->path_id = -1;
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
