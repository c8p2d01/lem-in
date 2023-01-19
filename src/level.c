/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:42:27 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/15 13:21:54 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void sort_links(t_graph *node)
{
	int i;
	int s;
	t_graph *swp;

	s = ft_array_size((void **)node->gates);
	i = 0;
	while ((i + 1) < s)
	{
		if ((node->gates[i])->lvl < (node->gates[(i + 1)])->lvl)
		{
			swp = node->gates[(i + 1)];
			node->gates[(i + 1)] = node->gates[i];
			node->gates[i] = swp;
			if (--i < 0)
				i = 0;
			continue ;
		}
		i++;
	}
}

void	level(globe *data)
{
	t_list	*q = ft_lstnew(data->start);
	t_list	*t = q;
	size_t	level = 0;
	size_t	count1 = 1;
	size_t	count2 = 0;
	while(q)
	{
		if (((t_graph *)(q->content))->lvl < 0)
			((t_graph *)(q->content))->lvl = level;
		for(int i = 0; ((t_graph *)(q->content))->gates[i] ; i++)
		{
			if (((t_graph *)(q->content))->gates[i]->lvl < 0)
			{
				(((t_graph *)(q->content))->gates[i])->lvl = level + 1;
				ft_lstadd_back(&q, ft_lstnew(((t_graph *)(q->content))->gates[i]));
				count2++;
			}
		}
		if (--count1 == 0)
		{
			level++;
			count1 = count2;
			count2 = 0;
		}
		dead_ends((t_graph *)q->content, data);
		sort_links((t_graph *)q->content);
		q = q->next;
	}
	ft_lstclear(&t, NULL);
}

void	level_sort(globe *data)
{
	t_graph	**s;
	t_graph	**r;
	ssize_t	l;

	s = ft_calloc(arraySize((void **)data->allNodes) + 1, sizeof(t_graph *));
	for (size_t i = 0; i < arraySize((void **)data->allNodes); i++)
	{
		if ((data->allNodes[i])->lvl < 0)
		{
			ft_g_del_node(data->allNodes[i]);
		}
		else
		{
			s[ft_array_size((void **)s)] = data->allNodes[i];
		}
	}
	r = ft_calloc(arraySize((void **)s) + 1, sizeof(t_graph *));
	l = 0;
	while (arraySize((void **)r) < arraySize((void **)s))
	{
		for (int i = 0; s[i]; i++)
		{
			if (s[i]->lvl == l)
				r[ft_array_size((void **)r)] = s[i];
		}
		l++;
	}
	free(data->allNodes);
	free(s);
	data->allNodes = r;
}