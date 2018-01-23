/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 05:11:02 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/23 21:46:50 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

void			ft_perror_buf(const char *str)
{
	ft_flush_buf();
	ft_setfd_buf(2);
	ft_putstr_buf(str);
	ft_putstr_buf(": ");
	ft_putstr_buf(ft_strerror(errno));
	ft_putchar_buf('\n');
	ft_flush_buf();
	ft_setfd_buf(1);
}

void			ft_perror(const char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(ft_strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void			ft_perror_file_buf(const char *str, const char *file)
{
	ft_flush_buf();
	ft_setfd_buf(2);
	ft_putstr_buf(str);
	ft_putstr_buf(": ");
	ft_putstr_buf(file);
	ft_putstr_buf(": ");
	ft_putstr_buf(ft_strerror(errno));
	ft_putchar_buf('\n');
	ft_flush_buf();
	ft_setfd_buf(1);
}

void			ft_perror_file(const char *str, const char *file)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(ft_strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}
