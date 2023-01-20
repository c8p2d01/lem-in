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

void	level(globe *data)
{
	t_list	*q = ft_lstnew(data->start);
	t_list	*t = q;
	size_t	level = 0;
	size_t	count1 = 1;
	size_t	count2 = 0;
	while(q)
	{
		if (((t_room *)(q->content))->lvl < 0)
			((t_room *)(q->content))->lvl = level;
		for(int i = 0; ((t_room *)(q->content))->links[i] ; i++)
		{
			if (((t_room *)(q->content))->links[i]->lvl < 0)
			{
				ft_lstadd_back(&q, ft_lstnew(((t_room *)(q->content))->links[i]));
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
	t_room	**s;
	t_room	**r;
	ssize_t	l;

	s = ft_calloc(arraySize((void **)data->graph) + 1, sizeof(t_room *));
	for (size_t i = 0; i < arraySize((void **)data->graph); i++)
	{
		if ((data->graph[i])->lvl < 0)
		{
			ft_g_del_node(data->graph[i]);
		}
		else
		{
			s[ft_array_size((void **)s)] = data->graph[i];
		}
	}
	r = ft_calloc(arraySize((void **)s) + 1, sizeof(t_room *));
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
	free(data->graph);
	free(s);
	data->graph = r;
}

/**
 * @brief Remove node that isn't connected to anywhere (not leveled)
 */
void	remove_useless(globe *data)
{
	for (size_t i = 0; data->graph[i]; ++i)
	{
		if (data->graph[i]->lvl == -1)
		{
			ft_g_del_node(data->graph[i]);
			ft_memmove(&data->graph[i], &data->graph[i + 1], sizeof(t_room *) * (ft_array_size((void **)&data->graph[i + 1]) + 1));
			--i;
		}
	}
}

/**
 * @brief Remove all deadend nodes
 */
void	remove_deadend(globe *data)
{
	for (size_t i = 0; data->graph[i]; ++i)
	{
		if (ft_array_size((void **)data->graph[i]->links) == 1)
		{
			ft_g_del_node(data->graph[i]);
			ft_memmove(&data->graph[i], &data->graph[i + 1], sizeof(t_room *) * (ft_array_size((void **)&data->graph[i + 1]) + 1));
			i = -1;
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
