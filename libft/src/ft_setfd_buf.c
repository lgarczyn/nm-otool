/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setfd_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 16:24:51 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/08 01:12:38 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_setfd_buf(int fd)
{
	static t_buffer	*buffer;

	if (buffer == NULL)
		buffer = ft_buf(NULL, 0, 0);
	if (buffer->fd != fd)
	{
		ft_flush_buf();
		buffer->fd = fd;
	}
}
