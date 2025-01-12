#include "../inc/lem_in.h"

/**
 * raising the mountain from which rivers flow
 * @brief set the level of each graph node depending on its distance to the
 * 	      start
 */
#include "../inc/lem_in.h"

void	tectonics()
{
	t_net	*net;
	t_list	*q_nodes;
	t_list	*new_q_node;
	t_list	*n_links;
	t_graph	*linked_to;

	net = *catch();
	if (!net)
		cut_loose();
	q_nodes = NULL;
	((t_content *)net->start->content)->level = 1;
	new_q_node = ft_lstnew(net->start);
	if (!new_q_node)
		cut_loose();
	ft_lstadd_back(&q_nodes, new_q_node);
	while (q_nodes)
	{
		n_links = ((t_graph *)q_nodes->content)->links;
		while (n_links)
		{
			if (((t_info *)((t_link *)n_links->content)->info)->active)
			{
				linked_to = ft_otherside((t_link *)n_links->content, q_nodes->content);
				if (((t_content *)linked_to->content)->level == 0 && 
					(((t_info *)((t_link *)n_links->content)->info)->flow == 0 ||
					!counter_flow(q_nodes->content, n_links->content)))
				{
					new_q_node = ft_lstnew(linked_to);
					if (!new_q_node)
					{
						ft_lstclear(&q_nodes, NULL);
						cut_loose();
					}
					((t_content *)((t_graph *)new_q_node->content)->content)->level = 
					((t_content *)((t_graph *)q_nodes->content)->content)->level + 1;
					ft_lstadd_back(&q_nodes, new_q_node);
				}
			}
			n_links = n_links->next;
		}
		q_nodes = q_nodes->next;
	}
	ft_lstclear(&q_nodes, NULL);
}

void	flow()
{
	t_net	*net;
	t_list	*river;
	t_list	*new_river_node;
	int		lowest_level_found;
	int		low_level;
	t_link	*low_link;
	t_list	*river_links;
	t_graph	*linked_to;
	t_list	*path;

	net = *catch();
	if (!net)
		cut_loose();
	new_river_node = ft_lstnew(net->end);
	if (!new_river_node)
		cut_loose();
	ft_lstadd_back(&river, new_river_node);
	while (river->content != net->start)
	{
		low_level = 69420;
		lowest_level_found = low_level;
		river_links = ((t_graph *)river->content)->links;
		while (river_links)
		{
			if (((t_info *)((t_link *)river_links->content)->info)->active)
			{
				linked_to = ft_otherside((t_link *)river_links->content, river->content);
				low_level = ((t_content *)linked_to->content)->level;
				if (counter_flow(river->content, river_links->content) &&
					low_level < lowest_level_found)
				{
					lowest_level_found = low_level;
					low_link = river_links->content;
				}
			}
			river_links = river_links->next;
		}
		linked_to = ft_otherside(low_link, river->content);
		if (((t_info *)low_link->info)->flow == 0)
			set_flow(river->content, low_link);
		if (counter_flow(river->content, low_link))
		{
			//printf("\t\t\tREFLUX\n");
			((t_info *)low_link->info)->active = false;
		}
		new_river_node = ft_lstnew(linked_to);
		ft_lstadd_back(&river, new_river_node);
		river = river->next;
	}
	if (net->pathed)
	{
		path = ft_lstnew(river);
		ft_lstadd_back(&net->paths, path);
	}
	else
		ft_lstclear(&river, NULL);
}

void	flatten()
{
	t_net	*net;
	t_list	*iterator;

	net = *catch();
	iterator = net->graph_nodes;
	while (iterator)
	{
		((t_content *)((t_graph *)iterator->content)->content)->level = 0;
		iterator = iterator->next;
	}
}

void	drain()
{
	t_net	*net;
	t_list	*iterator;

	net = *catch();
	iterator = net->graph_links;
	while (iterator)
	{
		if (((t_info *)((t_link *)iterator->content)->info)->active)
			((t_info *)((t_link *)iterator->content)->info)->flow = 0;
		iterator = iterator->next;
	}
}
