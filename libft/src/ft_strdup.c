/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 23:52:20 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/23 21:58:15 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*static_strdup(char const *s1, int len)
{
	int		i;
	char	*dup;

	dup = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char		*ft_strdup(char const *s1)
{
	int		len;

	len = ft_strlen(s1);
	return (static_strdup(s1, len));
}

char		*ft_strndup(char const *s1, int n)
{
	int		len;

	len = ft_strlen(s1);
	len = MIN(len, n);
	return (static_strdup(s1, len));
}
