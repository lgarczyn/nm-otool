/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 01:57:44 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/06 01:57:48 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	if (s2[0] == '\0')
		return ((char*)s1);
	if (!s1[0] || !n)
		return (NULL);
	i = 0;
	while ((s1[i] || !s2[i]) && i <= n)
		if (s2[i] == '\0')
			return ((char*)s1);
		else if (s1[i] == s2[i])
			i++;
		else
			break ;
	result = ft_strnstr(s1 + 1, s2, n - 1);
	return (result);
}
