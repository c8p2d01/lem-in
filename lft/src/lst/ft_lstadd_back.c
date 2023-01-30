/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:47 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/30 15:46:37 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*i;

	i = NULL;
	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		i = ft_lstlast((*lst));
		i->next = new;
		new->prev = i;
	}
}
