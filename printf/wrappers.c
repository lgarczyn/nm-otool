/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 16:31:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/09 04:09:57 by lgarczyn         ###   ########.fr       */
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
	return (ft_flush_buf());
}

int					printfd(int fd, const char *restrict format, ...)
{
	int				old_fd;
	size_t			total;

	old_fd = ft_buf(NULL, 0, 0)->fd;
	ft_setfd_buf(fd);
	ft_printf(format);
	total = ft_flush_total();
	ft_setfd_buf(old_fd);
	return (total);
}

int					printerr(const char *restrict format, ...)
{
	size_t			total;

	ft_setfd_buf(2);
	ft_printf(format);
	total = ft_flush_total();
	ft_setfd_buf(1);
	return (total);
}
