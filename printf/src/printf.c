/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 16:31:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/23 20:49:24 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

static bool			read_arg(const char **format, char arg)
{
	if (**format == arg)
	{
		(*format)++;
		return (true);
	}
	return (false);
}

static t_modifier	get_flags(const char **format)
{
	if (read_arg(format, '-'))
		return (m_left_justified | get_flags(format));
	if (read_arg(format, '+'))
		return (m_always_signed | get_flags(format));
	if (read_arg(format, ' '))
		return (m_plus_is_space | get_flags(format));
	if (read_arg(format, '#'))
		return (m_verbose | get_flags(format));
	if (read_arg(format, '0'))
		return (m_zero_padded | get_flags(format));
	return (m_none);
}

static t_length		get_input(const char **format)
{
	if (read_arg(format, 'h'))
	{
		if (read_arg(format, 'h'))
			return (l_hh);
		else
			return (l_h);
	}
	if (read_arg(format, 'l'))
	{
		if (read_arg(format, 'l'))
			return (l_ll);
		else
			return (l_l);
	}
	if (read_arg(format, 'j'))
		return (l_j);
	if (read_arg(format, 'z'))
		return (l_z);
	if (read_arg(format, 't'))
		return (l_t);
	return (l_none);
}

static int			get_width(const char **format, char starter)
{
	int				width;

	if (starter == '\0' || read_arg(format, starter))
	{
		if (**format < '0' || **format > '9')
		{
			return (0);
		}
		width = 0;
		while (**format >= '0' && **format <= '9')
		{
			width = width * 10 + (**format - '0');
			(*format)++;
		}
		return (width);
	}
	return (-1);
}

void				ft_printf(const char *restrict format, va_list ap)
{
	t_info			info;
	const char		*str;

	str = format;
	while (*str)
	{
		if (read_arg(&str, '%'))
		{
			info.modifiers = get_flags(&str);
			info.min_width = get_width(&str, '\0');
			info.precision = get_width(&str, '.');
			info.input_len = get_input(&str);
			display(*str, info, ap);
		}
		else
			ft_putchar_buf(*str);
		str++;
	}
}
