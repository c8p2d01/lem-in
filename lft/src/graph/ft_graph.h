/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:07 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/22 16:01:45 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GRAPH_H
# define FT_GRAPH_H

# define FLOW_ERROR 255

# include "../../inc/libft.h"

typedef struct s_room 
{
	struct s_link	**links;
	char			*name;
	size_t			x;
	size_t			y;
	ssize_t			lvl;
}	t_room;

typedef struct s_link 
{
	struct	s_room *vroom;
	int		flow;
	int		r_flow;
	struct	s_room *moorv;
	bool	active;
}	t_link;

t_room	*ft_g_new_node(char *data);

t_link	*ft_new_link(t_room *in, t_room *out);
bool	ft_is_link(t_link *link, t_room *a, t_room *b);
int		ft_flow(t_link *link, t_room *r);
t_link	*ft_active_link(t_link *link);

t_link	*ft_g_insert(t_room *node, t_room *next);

void	ft_g_unlink(t_room *a, t_room *b);

#endif