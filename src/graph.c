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
	if (data->linkedlist)
		free(data->linkedlist);
	if (data->graph)
		free(data->graph);
}

void reset_level(globe *data)
{
	for (int i = 0; data->graph[i]; i++)
	{
		if (data->graph[i] == data->start || data->graph[i] == data->end)
			continue;
		data->graph[i]->after_lvl = -1;

	}
	data->start->first_lvl = 0;
	data->start->after_lvl = 0;
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
		if (((t_room *)(q->content))->first_lvl < 0)
			((t_room *)(q->content))->first_lvl = level;
		for(int i = 0; ((t_room *)(q->content))->links[i] ; i++)
		{
			if (!((t_room *)(q->content))->links[i]->active)
				continue;
			if ((ft_otherside(((t_room *)(q->content))->links[i], (t_room *)(q->content)))->first_lvl < 0)
			{
				ft_lstadd_back(&q, ft_lstnew(ft_otherside(((t_room *)(q->content))->links[i], (t_room *)(q->content))));
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
	data->end->first_lvl = ++level;
	data->start->first_lvl = 0;
	ft_lstclear(&t, NULL);
}

void leveling(globe *data)
{
	t_list	*q = ft_lstnew(data->start);
	t_list	*t = q;
	t_room	*tmp = NULL;
	t_room	*lst = NULL;
	t_link	*link_next = NULL;
	size_t	level = 0;
	size_t	count1 = 1;
	size_t	count2 = 0;
	bool end = false;
	reset_level(data);
	while(q)
	{
		if ((t_room *)(q->content) == data->end)
		{
			printf("************\nEND\n");
			q = q->next;
			continue ;
		}
		if ((lst = (t_room *)(q->content))->after_lvl < 0)
			(lst)->after_lvl = level;
		for(int i = 0; (link_next = lst->links[i]) ; i++)
		{
			if (!ft_active_link(link_next))
				continue ;
			tmp = ft_otherside(link_next, lst);
			if ((t_room *)(q->content) == data->start && ft_flow(link_next, lst) == -1)
				continue;
			else if (tmp->after_lvl < 0 && ft_flow(link_next, lst) > -1)
			{
				ft_lstadd_back(&q, ft_lstnew(tmp));
				count2++;
			}
			if (tmp == data->end && ft_flow(link_next, lst) > -1)
				end = true;
		}
		if (--count1 == 0)
		{
			level++;
			count1 = count2;
			count2 = 0;
			// if (end)
			// 	break;
		}
		q = q->next;
	}
	data->end->after_lvl = level;
	data->start->after_lvl = 0;
	ft_lstclear(&t, NULL);
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



