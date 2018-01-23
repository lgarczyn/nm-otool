/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:33:25 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/08 21:37:56 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr_buf(int n)
{
	static char	buffer[11];
	int			i;
	int			isneg;
	int			len;

	len = ft_intlen(n);
	i = len - 1;
	isneg = n < 0;
	if (isneg)
	{
		buffer[0] = '-';
		buffer[i--] = '0' - (n % 10);
		n = -(n / 10);
	}
	while (i >= isneg)
	{
		buffer[i--] = '0' + (n % 10);
		n /= 10;
	}
	ft_putnstr_buf(buffer, len);
}
