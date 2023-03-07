/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:56 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/03/07 21:06:14 by cdahlhof         ###   ########.fr       */
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
		if (n)
			n->prev = p;
		if (p)
			p->next = n;
	}
	if (lst && del)
		del(lst->content);
	if (lst)
		free(lst);
	lst = NULL;
}

// int main()
// {
// 	t_list	*start = ft_lstnew("start");
// 	ft_lstadd_back(&start, ft_lstnew("next"));
// 	ft_lstadd_back(&start, ft_lstnew("last"));
// 	printf("b %p  n %p  l %p\n", start, start->next, start->next->next);
// 	ft_lstdelone(start->next, NULL);
// 	printf("b %p, n %p\n", start, start->next);
// }
