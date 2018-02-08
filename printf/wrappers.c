/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 16:31:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/08 01:13:05 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int					print(const char *restrict format, ...)
{
	char			buf[2048];

	ft_buf(buf, 2048, 1);
	ft_printf(format);
	return (ft_flush_buf());
}

int					printf(const char *restrict format, ...)
{
	ft_flush_total();
	ft_printf(format);
	return (ft_flush_total());
}

int					printfd(int fd, const char *restrict format, ...)
{
	ft_setfd_buf(fd);
	ft_printf(format);
	return (ft_flush_total());
}