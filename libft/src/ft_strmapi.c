/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 07:03:55 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/04 07:03:57 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*map;

	len = ft_strlen(s);
	map = (char*)malloc(len + 1);
	if (map == NULL)
		return (NULL);
	map[len] = '\0';
	i = -1;
	while (++i < len)
		map[i] = f((unsigned int)i, s[i]);
	return (map);
}
