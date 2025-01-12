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

/**
 * true	if	no flow is there
 * 			a flow exists but can be countered
 */
bool	counter_flow(t_graph *node, t_link *link)
{
	t_graph	*linked_to;

	linked_to = ft_otherside(link, node);
	if (((t_info *)link->info)->active)
	{
		if (((t_info *)link->info)->flow == 0)
			return (true);
		if ((((t_info *)link->info)->flow == -1 &&
			link->from == node)
			||
			(((t_info *)link->info)->flow == 1 &&
			link->to == node))
			return (true);
	}
	return (false);
}

/**
 * true	if a flow exists but can be countered
 */
void	set_flow(t_graph *node, t_link *link)
{
	t_graph	*linked_to;

	linked_to = ft_otherside(link, node);
	if (link->from == node)
		((t_info *)link->info)->flow = 1;
	if (link->from == linked_to)
		((t_info *)link->info)->flow = -1;
}

u_int8_t	name_color(char *in, int offset)
{
	u_int8_t	res;
	int		s;

	res = 0;
	s = ft_strlen(in);
	if (offset < s)
		res += in[offset++];
	if (offset < s)
		res += in[offset++];
	return (res);
}

#ifdef COLOR

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
		if (list->content/* == net->end || list->content == net->start*/)
		{
			graph = list->content;
			if (graph->content)
			{
				printf("node:    \e[48;2;%i;%i;%im %s \e[0m\tdst to start %i\n",
					name_color(((t_content *)graph->content)->name, 0),
					name_color(((t_content *)graph->content)->name, 2),
					name_color(((t_content *)graph->content)->name, 4),
					ft_strrchr(((t_content *)graph->content)->name, '_') ?
					ft_strrchr(((t_content *)graph->content)->name, '_') + 1 :
					((t_content *)graph->content)->name,
					((t_content *)graph->content)->level
					);
			}
			link = graph->links;
			while (link)
			{
				tmp = ft_otherside(link->content, graph);
				if (tmp && tmp->content)
				{
					printf("\t ᐅ \t");
					print_node(tmp);
				}
				link = link->next;
			}
			printf("\n");
		}
		list = list->next;
	}
			printf("\n");
			printf("\n");
}

void	print_node(void *iter)
{
	t_graph	*node;
	
	node = (t_graph *)iter;
	printf(" ᐅ \e[48;2;%i;%i;%im %s \e[0m\n",
		name_color(((t_content *)node->content)->name, 0),
		name_color(((t_content *)node->content)->name, 2),
		name_color(((t_content *)node->content)->name, 4),
		ft_strrchr(((t_content *)node->content)->name, '_') ?
			ft_strrchr(((t_content *)node->content)->name, '_') + 1 :
			((t_content *)node->content)->name);
}
#endif

#ifndef COLOR

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
		if (list->content/* == net->end || list->content == net->start*/)
		{
			graph = list->content;
			if (graph->content)
			{
				printf("node:    %s \tdst to start %i\n",
					ft_strrchr(((t_content *)graph->content)->name, '_') ?
					ft_strrchr(((t_content *)graph->content)->name, '_') + 1 :
					((t_content *)graph->content)->name,
					((t_content *)graph->content)->level
					);
			}
			link = graph->links;
			while (link)
			{
				tmp = ft_otherside(link->content, graph);
				if (((t_info *)((t_link *)link->content)->info)->active && tmp->content)
				{
					printf("\t ᐅ \t");
					print_node(tmp);
				}
				link = link->next;
			}
			printf("\n");
		}
		list = list->next;
	}
			printf("\n");
			printf("\n");
}

void	print_node(void *iter)
{
	t_graph	*node;
	
	node = (t_graph *)iter;
	printf(" ᐅ  %s \n",
		ft_strrchr(((t_content *)node->content)->name, '_') ?
			ft_strrchr(((t_content *)node->content)->name, '_') + 1 :
			((t_content *)node->content)->name);
}

void	print_node_and_links(void *iter)
{
	t_graph	*graph;
	t_graph	*tmp;
	t_list	*link;
	
	graph = (t_graph *)iter;
	if (graph->content)
	{
		printf("node:    %s \tdst to start %i\n",
			ft_strrchr(((t_content *)graph->content)->name, '_') ?
			ft_strrchr(((t_content *)graph->content)->name, '_') + 1 :
			((t_content *)graph->content)->name,
			((t_content *)graph->content)->level
			);
	}
	link = graph->links;
	while (link)
	{
		tmp = ft_otherside(link->content, graph);
		if (((t_info *)((t_link *)link->content)->info)->active && tmp->content)
		{
			printf("\t ᐅ \t");
			print_node(tmp);
		}
		link = link->next;
	}
}
#endif

void	print_path(void *iter)
{
	t_list	*path;
	
	path = (t_list *)iter;
	printf("Path Length %i\n", ft_lstsize(path));
	ft_lstiter(ft_lstfirst(path), print_node);
	printf("\n");
}

void	print_paths()
{
	t_net	*net;

	net = *catch();
	ft_lstiter(net->paths, print_path);
}
