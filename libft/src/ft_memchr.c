/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 23:49:57 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/03 23:49:59 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*src;
	unsigned char		uc;

	i = -1;
	uc = (unsigned char)c;
	src = (unsigned char*)s;
	while (++i < n)
		if (src[i] == uc)
			return (src + i);
	return (NULL);
}
