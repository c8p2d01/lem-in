#include "../inc/lem_in.h"

t_room * other_end(t_link *link, t_room *origin)
{
	if (link->vroom == origin)
		return (link->moorv);
	return (link->vroom);
}

/**
 * @brief Free globe struct
 */
void	freeGlobe(globe *data)
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

void	first_level(globe *data)
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
			if ((other_end(((t_room *)(q->content))->links[i], (t_room *)(q->content)))->lvl < 0)
			{
				ft_lstadd_back(&q, ft_lstnew(other_end(((t_room *)(q->content))->links[i], (t_room *)(q->content))));
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

void leveling(globe *data)
{
	t_list	*q = ft_lstnew(data->start);
	t_list	*t = q;
	t_room *tmp = NULL;
	size_t	level = 0;
	size_t	count1 = 1;
	size_t	count2 = 0;
	bool end = false;
	while(q)
	{
		if (((t_room *)(q->content))->lvl < 0)
			((t_room *)(q->content))->lvl = level;
		for(int i = 0; ((t_room *)(q->content))->links[i] ; i++)
		{
			if (!ft_active_link(((t_room *)(q->content))->links[i]))
				continue ;
			tmp = other_end(((t_room *)(q->content))->links[i], (t_room *)(q->content));
			if (tmp->lvl < 0 && !ft_flow(((t_room *)(q->content))->links[i], ((t_room *)(q->content))))
			{
				ft_lstadd_back(&q, ft_lstnew(other_end(((t_room *)(q->content))->links[i], (t_room *)(q->content))));
				count2++;
			}
			if (other_end(((t_room *)(q->content))->links[i], (t_room *)(q->content)) == data->end)
				end = true;
		}
		if (--count1 == 0)
		{
			level++;
			count1 = count2;
			count2 = 0;
			if (end)
				break;
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
