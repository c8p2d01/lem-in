/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:07 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/14 15:24:16 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GRAPH_H
# define FT_GRAPH_H

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
	struct s_room *vroom;
	int flow;
	int r_flow;
	struct s_room *broom;
}	t_link;

t_room	*ft_g_new_node(char *data);

void	ft_g_insert(t_room *node, size_t amount, ...);
void	ft_g_insert_single(t_room *node, t_room *next);

void	ft_g_clean(t_room *node);
void	print_nodes(t_room **node);
bool	ft_has_gate(t_room *node, t_room *next);

void	ft_g_del_node(t_room *node);
void	ft_g_unlink(t_room *a, t_room *b);

#endif