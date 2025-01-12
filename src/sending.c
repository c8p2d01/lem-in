#include "../inc/lem_in.h"

void	send_off()
{
	t_net		*net;
	int			ant;
	int			ant_endet;
	t_list		*pick_path;
	t_list		*path_node;
	t_content	*stuff;

	net = *catch();
	ant = 1;
	ant_endet = 0;
	printf("\n");
	while (ant_endet < net->packets)
	{
		pick_path = net->paths;
		while (pick_path)
		{
			path_node = ft_lstfirst(pick_path->content);
			while (path_node && path_node->next)
			{
				if (((t_content *)((t_graph *)path_node->next->content)->content)->ant != -1)
				{
					printf("L%i-%s ", ((t_content *)((t_graph *)path_node->next->content)->content)->ant,
						((t_content *)((t_graph *)path_node->content)->content)->name);
					if (((t_graph *)path_node->content) == net->end)
						ant_endet++;
				}
					((t_content *)((t_graph *)path_node->content)->content)->ant = 
					((t_content *)((t_graph *)path_node->next->content)->content)->ant;
				if (((t_graph *)path_node->next->content) == net->start)
				{
					if (ant - 1 < net->packets)
					{
						((t_content *)((t_graph *)path_node->content)->content)->ant = ant;
						printf("L%i-%s ", ant, ((t_content *)((t_graph *)path_node->content)->content)->name);
						ant++;
					}
				}
				path_node = path_node->next;
			}
			pick_path = pick_path->next;
		}
		printf("\n");
	}
}

void	path_start(t_list *path)
{
	t_list	*path_node;

	path_node = path;
	while (path_node && path_node->next)
	{
		if (((t_content *)((t_graph *)path_node->content)->content)->ant != -1)
		{
			((t_content *)((t_graph *)path_node->next->content)->content)->ant =
			((t_content *)((t_graph *)path_node->content)->content)->ant;
		}
		path_node = path_node->next;
	}
}

void	path_step(t_list *path)
{
	t_list	*path_node;

	path_node = path;
	while (path_node && path_node->next)
	{
		((t_content *)((t_graph *)path_node->content)->content)->ant =
		((t_content *)((t_graph *)path_node->next->content)->content)->ant;
		path_node = path_node->next;
	}
	((t_content *)((t_graph *)path_node->content)->content)->ant = -1;
}

void	path_step_print(t_list *path)
{
	t_list	*path_node;

	path_node = path;
	while (path_node)
	{
		if (((t_content *)((t_graph *)path_node->content)->content)->ant != -1)
		{
			printf("L%i-%s\t",
				((t_content *)((t_graph *)path_node->content)->content)->ant,
				((t_content *)((t_graph *)path_node->content)->content)->name);
		}
		path_node = path_node->next;
	}
}

// (t_content *)((t_graph *)((t_list *)(net->paths)->content)->content)->content