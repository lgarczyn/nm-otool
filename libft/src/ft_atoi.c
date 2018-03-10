/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 05:11:02 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/10 23:54:31 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_pure_atoi(const char *str)
{
	int		value;
	int		i;

	i = 0;
	value = 0;
	while (ft_isdigit(str[i]) && i <= 10)
		value = value * 10 + str[i++] - '0';
	return value;
}

int			ft_atoi(const char *str)
{
	int		value;
	int		sign;
	int		i;

	if (str == NULL || *str == 0)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 0;
	if (str[i] == '-' || str[i] == '+')
		sign = i++;
	value = ft_pure_atoi(str + i);
	return ((str[sign] == '-') ? -value : value);
}
