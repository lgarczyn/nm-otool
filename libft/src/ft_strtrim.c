/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 03:29:05 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/06 03:29:07 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char		*ft_strtrim(char const *s)
{
	int		start;
	int		len;
	char	*ret;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (s[start] && ft_isempty(s[start]))
		start++;
	len = ft_strlen(s);
	while (--len > 0 && ft_isempty(s[len]))
		;
	len = len - start + 1;
	if (len <= 0)
	{
		ret = malloc(1);
		*ret = 0;
		return (ret);
	}
	return (ft_strsub(s, start, len));
}
