/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupwhile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:53:57 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/28 20:40:29 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndupwhile(const char *m, size_t n, int (*pred)(int c))
{
	size_t	i;

	i = 0;
	while (pred(m[i]) && i < n)
		i++;
	return (ft_strndup(m, i));
}

char		*ft_strdupwhile(const char *m, int (*pred)(int c))
{
	size_t	i;

	i = 0;
	while (pred(m[i]))
		i++;
	return (ft_strndup(m, i));
}
