/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:07 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/29 16:50:55 by cdahlhof         ###   ########.fr       */
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
	ssize_t			first_lvl;
	ssize_t			after_lvl;
}	t_room;

typedef struct s_link
{
	struct	s_room *vroom;
	int		flow;
	struct	s_room *moorv;
	bool	active;
}	t_link;

t_room	*ft_g_new_room(char *name);
void    print_nodes(t_room **node);

t_link	*ft_new_link(t_room *in, t_room *out);
bool	ft_is_link(t_link *link, t_room *a, t_room *b);
t_link	*ft_active_link(t_link *link);
int		ft_flow(t_link *link, t_room *node);
bool	ft_has_link(t_room *a, t_room *b);
t_room	*ft_otherside(t_link *link, t_room *myside);
size_t	ft_active_link_size(t_room *node);

t_link	*ft_g_insert(t_room *node, t_room *next);

void	ft_g_unlink(t_room *a, t_room *b);
void	ft_g_del_node(t_room *node);
void ft_setflow(t_link *link, t_room *next);
void ft_resetflow(t_link *link, t_room *next);

#endif
