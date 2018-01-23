/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 05:11:02 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/04 05:11:03 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		value;
	int		sign;
	int		i;

	if (str == NULL || ft_strlen(str) == 0)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 0;
	if (str[i] == '-' || str[i] == '+')
		sign = i++;
	value = 0;
	while (str[i])
		if (ft_isdigit(str[i]))
			value = value * 10 + str[i++] - '0';
		else
			break ;
	return ((str[sign] == '-') ? -value : value);
}
