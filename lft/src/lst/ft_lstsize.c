/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:42:16 by cdahlhof          #+#    #+#             */
/*   Updated: 2023/01/29 16:17:00 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && lst->prev)
		lst = lst->prev;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
