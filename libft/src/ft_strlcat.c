/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 06:25:21 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/06 06:25:23 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	a;

	i = 0;
	j = ft_strlen(dst);
	a = j + ft_strlen(src);
	if (size < ft_strlen(dst))
		return (ft_strlen(src) + size);
	while (src[i] && size > j + 1)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (a);
}
