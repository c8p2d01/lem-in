#include "../inc/lem_in.h"

void	clear_graph(void *graph)
{
	t_graph	*node;

	node = (t_graph *)graph;
	if (!node)
		return ;
	if (node->content)
	{
		if (((t_content *)node->content)->name)
			free(((t_content *)node->content)->name);
		free (node->content);
	}
	free (node);
}

void	clear_link(void *link)
{
	if (!link)
		return ;
	if (((t_link *)link)->info)
	{
		free (((t_link *)link)->info);
	}
	free (link);
}

void	cut_loose()
{
	t_net	*net;
	t_list	*lst;
	t_list	*tmp;

	net = *catch();
	if (!net)
		return;
	ft_lstclear(&net->graph_links, clear_link);
	if (net->graph_links)
		free (net->graph_links);
	ft_lstclear(&net->graph_nodes, clear_graph);
	if (net->graph_nodes)
		free (net->graph_nodes);
	exit(1);
}

void	prune_orphans()
{
	t_net	*net;
	t_list	*node;
	t_list	*next;
	t_graph	*orph;

	net = *catch();
	if (!net || !net->graph_nodes)
		return;
	node = net->graph_nodes;
	while (node)
	{
		next = node->next;
		if (node->content)
		{
			orph = node->content;
			if (!orph->links || ft_lstsize(orph->links) == 0)
				ft_lstdelone(node, clear_graph);
		}
		node = next;
	}
}

void	deactivate_ends()
{
	t_net	*net;
	t_list	*node;
	t_list	*next;
	t_list	*link;
	t_graph	*end;

	net = *catch();
	if (!net || !net->graph_nodes)
		return;
	node = net->graph_nodes;
	while (node)
	{
		next = node->next;
		if (node->content)
		{
			end = node->content;
			if (end != net->end && end != net->start && \
				ft_lstsize(end->links) == 1)
			{
				((t_info *)((t_link *)end->links->content)->info)->active = false;
			}
		}
		node = next;
	}
}

void	prune_subnets()
{
	t_net		*net;
	t_list		*node;
	t_list		*next;
	t_content	*stuff;

	net = *catch();
	if (!net || !((t_content *)((t_graph *)net->start)->content)->level)
		return ;
	node = net->graph_nodes;
	while (node)
	{
		next = node->next;
		stuff = (t_content *)((t_graph *)node->content)->content;
		if (stuff->level == 0)
		{
			ft_lstdelone(node, clear_graph);
			node = NULL;
		}
		node = next;
	}
}
