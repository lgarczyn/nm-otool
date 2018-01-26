/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnendl_buf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:32:39 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:46:24 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnendl_buf(const char *str, size_t len)
{
	ft_putnstr_buf(str, len);
	ft_putchar_buf('\n');
}
