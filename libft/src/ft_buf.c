/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:24:37 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/08 21:36:37 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_buffer			*ft_buf(char *buffer, size_t size, int fd)
{
	static t_buffer	buf;

	if (buffer)
	{
		buf.buffer = buffer;
		buf.size = size;
		buf.pos = 0;
		buf.total = 0;
		buf.fd = fd;
		return (NULL);
	}
	else
		return (&buf);
}
