/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:23:18 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/08 21:37:06 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putchar_buf(char c)
{
	static t_buffer	*buffer;

	if (!buffer)
		buffer = ft_buf(NULL, 0, 0);
	buffer->buffer[buffer->pos++] = c;
	buffer->total++;
	if (buffer->pos >= buffer->size)
		ft_flush_buf_overflow();
}
