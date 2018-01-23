/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 02:48:56 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/06 02:48:57 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	size_t		len;

	len = ft_strlen(s);
	if (s[len] == (char)c)
		return ((char *)s + len);
	while (len-- > 0)
		if (s[len] == (char)c)
			return ((char *)s + len);
	return (NULL);
}
