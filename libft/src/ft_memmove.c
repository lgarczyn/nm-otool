/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:58:49 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/03 19:58:51 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*source;
	char		*destin;

	if (dst == NULL || src == NULL)
		return (dst);
	source = (char*)src;
	destin = (char*)dst;
	if (source < destin)
	{
		i = len;
		while (i-- > 0)
			destin[i] = source[i];
	}
	else if (source > destin)
	{
		i = -1;
		while (++i < len)
			destin[i] = source[i];
	}
	return (dst);
}
