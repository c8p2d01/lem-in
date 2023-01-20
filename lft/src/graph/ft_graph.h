/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:07 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/19 17:51:22 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GRAPH_H
# define FT_GRAPH_H

# include "../../inc/libft.h"

typedef struct t_graph {
	struct t_link	**links;
	char			*name;
	size_t			x;
	size_t			y;
	ssize_t			lvl;
	float			frate;
}	t_graph;

typedef struct t_link {
	t_graph *next;
	t_graph *prev;
	double	fCapa;
	double	bCapa;
	bool	active;
}	t_link;

t_graph	*ft_g_new_node(char *data);

void	ft_g_insert(t_graph *node, size_t amount, ...);
void	ft_g_insert_single(t_graph *node, t_graph *next);

void	ft_g_clean(t_graph *node);
void	print_nodes(t_graph **node);
bool	ft_has_gate(t_graph *node, t_graph *next);

void	ft_g_del_node(t_graph *node);
void	ft_g_unlink(t_graph *a, t_graph *b);

#endif