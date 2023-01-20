/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:06:49 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/02 19:06:49 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

/**
 * @brief Insert one node to another
 */
t_link	*ft_g_insert(t_room *node, t_room *next)
{
	t_link	*con =ft_new_link(node, next);

	size_t	i = 0;
	if (node->links == NULL)
	{
		node->links = ft_calloc(2, sizeof(t_link *));
		node->links[i] = con;
	}
	else
	{
		while (node->links[i] && !ft_is_link(node->links[i], con->moorv, con->vroom))
			i++;
		if (!node->links[i])
		{
			node->links = ft_realloc(node->links, sizeof(t_link *) * (i + 1), sizeof(t_link *));
			node->links[i] = con;
		}
	}

	size_t	j = 0;
	if (con->moorv->links == NULL)
	{
		con->moorv->links = ft_calloc(2, sizeof(t_link *));
		con->moorv->links[j] = con;
	}
	else
	{
		while (con->moorv->links[j] && !ft_is_link(con->moorv->links[j], con->moorv,  con->vroom))
			j++;
		if (!con->moorv->links[j])
		{
			con->moorv->links = ft_realloc(con->moorv->links, sizeof(t_link *) * (j + 1), sizeof(t_link *));
			con->moorv->links[j] = con;
		}
	}
	return (con);
}


void    print_nodes(t_room **node)
{
    for (size_t i = 0; node[i]; ++i)
    {
        printf("node '%s'\tlevel %li\n", node[i]->name, node[i]->lvl);
        for (size_t j = 0; node[i]->links && node[i]->links[j]; ++j)
        {
            printf("\t link to '%s'\n", (otherside(node[i]->links[j], node[i]))->name);
        }
    }
}

int main()
{
	t_room *a = ft_g_new_node("eins");
	t_room *b = ft_g_new_node("zwei");
	t_room *c = ft_g_new_node("drei");
	t_room *d = ft_g_new_node("vier");
	t_room *arr[5];

	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
	arr[4] = NULL;

	ft_g_insert(a, b);
	ft_g_insert(b, c);
	ft_g_insert(b, d);
	ft_g_insert(c, d);
	ft_g_insert(a, c);

	print_nodes(arr);
}