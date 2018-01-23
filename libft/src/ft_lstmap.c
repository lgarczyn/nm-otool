/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 21:53:14 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 21:53:15 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*prev;

	first = f(lst);
	prev = first;
	while (lst->next)
	{
		prev->next = f(lst->next);
		prev = prev->next;
		lst = lst->next;
		if (prev == NULL)
			return (NULL);
	}
	prev->next = NULL;
	return (first);
}
