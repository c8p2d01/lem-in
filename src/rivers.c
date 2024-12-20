#include "../inc/lem_in.h"

/**
 * raising the mountain from which rivers flow
 * @brief set the level og each grapg node depending on its distance to the
 * 	      start
 */
void	tectonics()
{
	t_net	*net;
	t_list	*nodes;//nodes to visit
	t_list	*iterator;
	t_list	*links;
	t_graph	*linked_to;
	int		count = 1;

	net = *catch();
	ft_lstadd_back(&nodes, ft_lstnew(net->start));
	((t_content *)net->start->content)->level = 1;
	iterator = nodes;
	while (iterator)
	{
		links = ((t_graph *)iterator->content)->links;
		while (links)
		{
			linked_to = ft_otherside((t_link *)links->content, iterator->content);
			if (((t_content *)linked_to->content)->level == 0)
			{
				((t_content *)linked_to->content)->level =
				((t_content *)((t_graph *)iterator->content)->content)->level + 1;
				ft_lstadd_back(&nodes, ft_lstnew(linked_to));
				count ++;
			}
			links = links->next;
		}
		iterator = iterator->next;
	}
}


