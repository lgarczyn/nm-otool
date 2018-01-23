/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 23:29:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 23:29:34 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcpy(char *dst, const char *src)
{
	int		i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	while (dst[i])
		dst[i++] = '\0';
	return (dst);
}
