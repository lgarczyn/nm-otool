/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putrnstr_buf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:32:17 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:46:21 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putrnstr_buf(const char *str, size_t len)
{
	size_t			i;

	i = len;
	while (i-- > 0)
		ft_putchar_buf(str[i]);
}
