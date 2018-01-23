/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_fast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 23:08:16 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 23:08:19 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlen_fast(const char *s)
{
	unsigned	*ptr;

	ptr = (unsigned*)s;
	while (1)
	{
		if ((*ptr & 0xFF) == 0)
			return ((const char*)ptr - s);
		if ((*ptr & 0xFF00) == 0)
			return ((const char*)ptr - s + 1);
		if ((*ptr & 0xFF0000) == 0)
			return ((const char*)ptr - s + 2);
		if ((*ptr & 0xFF000000) == 0)
			return ((const char*)ptr - s + 3);
		++ptr;
	}
	return (-1);
}
