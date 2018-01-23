/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwstr_buf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:32:17 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/08 21:32:25 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnwstr_buf(wchar_t *str, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
		ft_putwchar_buf(str[i++]);
}
