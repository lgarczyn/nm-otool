/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:28:02 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/03 19:28:06 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	value;
	unsigned char	*source;
	unsigned char	*destin;

	if (dst == NULL || src == NULL)
		return (dst);
	source = (unsigned char*)src;
	destin = (unsigned char*)dst;
	value = (unsigned char)c;
	i = -1;
	while (++i < n)
		if (source[i] != value)
			destin[i] = source[i];
		else
		{
			destin[i] = value;
			return (destin + i + 1);
		}
	return (NULL);
}
