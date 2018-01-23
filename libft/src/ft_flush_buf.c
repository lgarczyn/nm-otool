/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 21:34:00 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/08 21:34:07 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int					ft_flush_buf(void)
{
	static t_buffer	*buffer;
	size_t			ret;

	if (!buffer)
		buffer = ft_buf(NULL, 0, 0);
	ft_flush_buf_overflow();
	ret = buffer->total;
	buffer->total = 0;
	buffer->pos = 0;
	return (ret);
}
