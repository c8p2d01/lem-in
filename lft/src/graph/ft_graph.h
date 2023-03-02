/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:07 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/02/28 17:11:03 by cdahlhof         ###   ########.fr       */
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
	bool			flown;
}	t_room;

typedef struct s_link
{
	struct	s_room *vroom;
	int		flow;
	struct	s_room *moorv;
	bool	active;
}	t_link;

t_room	*ft_g_new_room(char *name);
t_link	*ft_new_link(t_room *in, t_room *out);
void	ft_g_del_node(t_room *node);

t_link	*ft_g_insert(t_room *node, t_room *next);
void	ft_g_unlink(t_room *a, t_room *b);

bool	ft_is_link(t_link *link, t_room *a, t_room *b);
bool	ft_has_link(t_room *a, t_room *b);

t_link	*ft_active_link(t_link *link);

void	dry(t_room **all);
int		ft_flow(t_link *link, t_room *node);
void	ft_setflow(t_link *link, t_room *next);
void	ft_resetflow(t_link *link, t_room *next);

t_room	*ft_otherside(t_link *link, t_room *myside);

size_t	ft_active_link_size(t_room *node);
size_t	ft_flow_link_size(t_room *node);

void	print_nodes(t_room **node);
void	print_node(t_room *node);

#endif
