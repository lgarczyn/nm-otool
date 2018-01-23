/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush_buf_overflow.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:34:00 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/08 21:34:07 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void				ft_flush_buf_overflow(void)
{
	static t_buffer	*buffer;
	size_t			ret;

	if (!buffer)
		buffer = ft_buf(NULL, 0, 0);
	ret = write(buffer->fd, buffer->buffer, buffer->pos);
	if (ret == (size_t)-1)
		ft_perror(NULL);
	buffer->pos = 0;
}
