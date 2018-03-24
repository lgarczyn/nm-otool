/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 16:31:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/23 20:49:25 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdarg.h>

int					print_ind(const char *restrict format, ...)
{
	char			buf[2048];
	va_list			ap;

	ft_buf(buf, 2048, 1);
	va_start(ap, format);
	ft_printf(format, ap);
	va_end(ap);
	return (ft_flush_buf());
}

int					print(const char *restrict format, ...)
{
	va_list			ap;

	ft_flush_total();
	va_start(ap, format);
	ft_printf(format, ap);
	va_end(ap);
	return (ft_flush_buf());
}

int					printerr(const char *restrict format, ...)
{
	size_t			total;
	va_list			ap;

	ft_setfd_buf(2);
	va_start(ap, format);
	ft_printf(format, ap);
	va_end(ap);
	total = ft_flush_total();
	ft_setfd_buf(1);
	return (total);
}

int					printfd(int fd, const char *restrict format, ...)
{
	int				old_fd;
	size_t			total;
	va_list			ap;

	old_fd = ft_buf(NULL, 0, 0)->fd;
	ft_setfd_buf(fd);
	va_start(ap, format);
	ft_printf(format, ap);
	va_end(ap);
	total = ft_flush_total();
	ft_setfd_buf(old_fd);
	return (total);
}
