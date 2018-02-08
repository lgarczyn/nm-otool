/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush_overflow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:34:00 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/08 00:37:26 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void				ft_flush_overflow(void)
{
	static t_buffer	*buffer;
	ssize_t			ret;

	if (!buffer)
		buffer = ft_buf(NULL, 0, 0);
	ret = write(buffer->fd, buffer->buffer, buffer->pos);
	if (ret == -1)
		ft_perror(NULL);
	buffer->pos = 0;
}
