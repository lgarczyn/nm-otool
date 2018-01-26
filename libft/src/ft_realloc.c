/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 16:19:51 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:46:19 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			*ft_realloc(void *ptr, size_t size)
{
	void		*mem;

	if (!ptr && size)
		return (ft_memalloc(size));
	if (!ptr)
		return (ft_memalloc(1));
	mem = ft_memalloc(size);
	ft_memmove(mem, ptr, size);
	free(ptr);
	return (mem);
}
