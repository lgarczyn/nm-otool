/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_buf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 17:24:26 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/08/31 17:24:30 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putwchar_buf(wchar_t wc)
{
	int				i;
	char			cs[3];

	if (wc < 0x80)
	{
		ft_putchar_buf(wc);
		return ;
	}
	i = 0;
	while (i < 3 && wc & ~(0x3F >> i))
	{
		cs[i++] = (wc & 0x3F) | 0x80;
		wc >>= 6;
	}
	ft_putchar_buf((wc & 0x3F >> i) | (0xF0 << (3 - i)));
	while (i--)
		ft_putchar_buf(cs[i]);
}
