/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 22:21:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 22:21:31 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content_size = 0;
	new->content = NULL;
	new->next = NULL;
	if (content)
	{
		new->content_size = content_size;
		new->content = (void*)malloc(content_size);
		if (new->content == NULL)
			return (NULL);
		ft_memcpy(new->content, content, content_size);
	}
	return (new);
}
