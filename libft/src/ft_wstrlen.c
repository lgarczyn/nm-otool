/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 23:08:16 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/08/31 19:12:47 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_wstrlen(const wchar_t *s)
{
	const wchar_t	*ptr;

	ptr = s;
	while (*ptr)
		ptr++;
	return (ptr - s);
}
