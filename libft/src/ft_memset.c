/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:36:58 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/03 16:37:01 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;
	unsigned char	val;
	size_t			i;

	if (b == NULL)
		return (NULL);
	dst = (unsigned char *)b;
	val = (unsigned char)c;
	i = -1;
	while (++i < len)
		dst[i] = val;
	return (b);
}
