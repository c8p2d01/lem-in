/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:56 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/29 16:19:56 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*n = NULL;
	t_list	*p = NULL;
	if (lst)
	{
		n = lst->next;
		p = lst->prev;
		n->prev = p;
		p->next = n;
	}
	if (lst && del)
		del(lst->content);
	free(lst);
}
