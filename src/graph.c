#include "../inc/lem_in.h"

/**
 * @brief Free globe struct
 */
void	free_globe(globe *data)
{
	for (size_t i = 0; data->graph && data->graph[i] != NULL; ++i)
	{
		if (data->graph[i]->name)
			unreach(data->graph[i]->name);
		if (data->graph[i]->links)
			unreach(data->graph[i]->links);
		unreach(data->graph[i]);
	}
	if (data->graph)
		unreach(data->graph);
	for (size_t i = 0; data->linkedlist && data->linkedlist[i] != NULL; ++i)
	{
		unreach(data->linkedlist[i]);
	}
	if (data->linkedlist)
		unreach(data->linkedlist);
	for (size_t i = 0; data->paths && data->paths[i] != NULL; ++i)
	{
		if (data->paths[i]->path)
			unreach(data->paths[i]->path);
		unreach(data->paths[i]);
	}
	if (data->paths)
		unreach(data->paths);
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
	t_list	*queue = ft_lstnew(data->start);
	t_list	*temp = queue;
	t_room	*current;
	size_t	level = 0;
	size_t	group_0 = 1;
	size_t	new_group = 0;

	while (queue)
	{
		current = ((t_room*)(queue->content));
		if (current->first_lvl == -1)
			current->first_lvl = level;
		for (int i = 0; current->links[i]; i++)
		{
			if (!ft_active_link(current->links[i]))
				continue ;
			if (ft_otherside(current->links[i], current)->first_lvl == -1)
			{
				ft_lstadd_back(&queue, ft_lstnew(ft_otherside(current->links[i], current)));
				new_group++;
			}
		}
		if (--group_0 == 0)
		{
			group_0 = new_group;
			new_group = 0;
			level++;
		}
		queue = queue->next;
	}
	ft_lstclear(&temp, NULL);
}

void leveling(globe *data)
{
	t_list	*queue = ft_lstnew(data->start);
	t_list	*t = queue;
	t_room	*current = NULL;
	t_room	*target = NULL;
	t_link	*target_link = NULL;
	size_t	level = 0;
	size_t	group_0 = 1;
	size_t	new_group = 0;
	bool end = false;

	reset_level(data);

	while(queue)
	{
		current =(t_room *)(queue->content);

		if (current == data->end)
		{
			queue = queue->next;
			continue ;
		}
		if (current->after_lvl < 0)
			current->after_lvl = level;
		for(int i = 0; (target_link = current->links[i]) ; i++)
		{
			if (!ft_active_link(target_link))
				continue ;
			target = ft_otherside(target_link, current);
			if (current == data->start && ft_flow(target_link, current) == COUNTERFLOW)
				continue;
			else if (target->after_lvl < 0 && ft_flow(target_link, current) < COUNTERFLOW)
			{
				if (target == data->end && ft_flow(target_link, current) != NOFLOW)
					continue;
				ft_lstadd_back(&queue, ft_lstnew(target));
				new_group++;
			}
			if (target == data->end && ft_flow(target_link, current) == NOFLOW)
				end = true;
		}
		if (--group_0 == 0)
		{
			level++;
			group_0 = new_group;
			new_group = 0;
			if (end)
				break;
		}
		queue = queue->next;
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
		if (ft_active_link_size(data->graph[i]) < 2 && !(data->graph[i] == data->start || data->graph[i] == data->end))
		{
			ft_g_del_node(data->graph[i]);
			ft_memmove(&data->graph[i], &data->graph[i + 1], sizeof(t_room *) * (ft_array_size((void **)&data->graph[i + 1]) + 1));
			i = -1;
		}
	}
}



