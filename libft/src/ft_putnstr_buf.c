/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:32:17 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/23 21:29:23 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnstr_buf(const char *str, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
		ft_putchar_buf(str[i++]);
}
