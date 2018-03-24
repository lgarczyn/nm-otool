/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmstr_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:32:17 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/18 20:03:34 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putmstr_buf(const char *str, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len && str[i])
		ft_putchar_buf(str[i++]);
}
