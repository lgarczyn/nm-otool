/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 17:17:36 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/25 17:17:38 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					ft_intlen(int num)
{
	int				sign;

	sign = (num < 0);
	if (!sign)
		num = -num;
	if (num <= -1000000000)
		return (10 + sign);
	if (num <= -100000000)
		return (9 + sign);
	if (num <= -10000000)
		return (8 + sign);
	if (num <= -1000000)
		return (7 + sign);
	if (num <= -100000)
		return (6 + sign);
	if (num <= -10000)
		return (5 + sign);
	if (num <= -1000)
		return (4 + sign);
	if (num <= -100)
		return (3 + sign);
	if (num <= -10)
		return (2 + sign);
	return (1 + sign);
}
