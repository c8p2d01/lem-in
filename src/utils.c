#include "../inc/lem_in.h"

t_graph	*node_exist(char	*name)
{
	t_net	*net;
	t_list	*node;

	net = *catch();
	if (!net || !net->graph_nodes)
		return (NULL);
	node = net->graph_nodes;
	while (node)
	{
		if (node->content && \
			((t_content *)((t_graph *)node->content)->content) && \
			((t_content *)((t_graph *)node->content)->content)->name && \
			!ft_strncmp(
				((t_content *)((t_graph *)node->content)->content)->name,
				name,
				ft_strlen(name) + 1))
		{
			return (node->content);
		}
		node = node->next;
	}
	return (NULL);
}

void	print_net()
{
	t_net	*net;
	t_list	*list;
	t_graph	*graph;
	t_graph	*tmp;
	t_list	*link;

	net = *catch();

	if (!net || !net->graph_nodes)
		return ;
	list = net->graph_nodes;
	while (list)
	{
		if (list->content)
		{
			graph = list->content;
			if (graph->content)
				printf("node:    %s\t%i(%i|%i)\n",
					((t_content *)graph->content)->name,
					((t_content *)graph->content)->level,
					((t_content *)graph->content)->x,
					((t_content *)graph->content)->y);
			link = graph->links;
			while (link)
			{
				tmp = ft_otherside(link->content, graph);
				if (tmp && tmp->content)
					printf("\t ᐅ %s\n", ((t_content *)tmp->content)->name);
				link = link->next;
			}
		}
		list = list->next;
	}
}
