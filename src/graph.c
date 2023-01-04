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
