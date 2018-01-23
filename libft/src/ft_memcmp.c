/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 23:50:10 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/03 23:50:11 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*str1;
	unsigned char		*str2;

	i = -1;
	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	while (++i < n)
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	return (0);
}
