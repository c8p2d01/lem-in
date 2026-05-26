#include "../inc/lem_in.h"

int		interrupt(char *format, ...)
{
	va_list		arg;
	t_hook		*params;

	params = *vis();
	mlx_terminate(params->mlx);
	va_start(arg, format);
	if (format)
		ft_vprintf(format, arg);
	ft_clean_allocs();
	exit(-1);
}

//void	prune_subnets()
//{
//	t_net		*net;
//	t_list		*node;
//	t_list		*next;
//	t_content	*stuff;

//	net = *catch();
//	if (!net || !((t_content *)((t_graph *)net->start)->content)->level)
//		return ;
//	node = net->graph_nodes;
//	while (node)
//	{
//		next = node->next;
//		stuff = (t_content *)((t_graph *)node->content)->content;
//		if (stuff->level == 0)
//		{
//			ft_lstdelone(node, clear_graph);
//			node = NULL;
//		}
//		node = next;
//	}
//}
