/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_fast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 22:50:21 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/08 22:50:43 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strcmp_fast(const char *str0, const char *str1, int len)
{
	int			i;
	int			max;
	size_t		*ptr0;
	size_t		*ptr1;

	ptr0 = (size_t*)str0;
	ptr1 = (size_t*)str1;
	max = len / sizeof(size_t);
	i = 0;
	while (i < max)
		if (ptr0[i] != ptr1[i])
			break ;
		else
			i++;
	i *= sizeof(size_t);
	while (i < len)
		if (str0[i] != str1[i])
			return (str0[i] - str1[i]);
		else
			i++;
	if (str0[i] != str1[i])
		return (str0[i] - str1[i]);
	return (0);
}
