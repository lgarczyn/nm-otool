/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 23:08:16 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:41:12 by lgarczyn         ###   ########.fr       */
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
