/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:49:28 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 16:49:29 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		len;
	int		i;

	len = 1;
	i = n;
	while ((i /= 10) != 0)
		len++;
	sign = (n < 0);
	str = (char*)malloc(len + sign + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
		str[i++] = '-';
	n = (n < 0) ? n : -n;
	str[len + sign] = '\0';
	while (--len >= 0)
	{
		str[len + sign] = '0' - (n % 10);
		n /= 10;
	}
	return (str);
}
