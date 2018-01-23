/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 13:14:41 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/23 20:59:07 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printf.h"
#include <stdarg.h>

static char			getc(t_info info)
{
	return (info.modifiers & m_zero_padded ? '0' : ' ');
}

void				putchar_padded(int c, t_info info)
{
	if (!(info.modifiers & m_left_justified))
		ft_putnchar_buf(getc(info), info.min_width - 1);
	if (info.input_len == l_l)
		ft_putwchar_buf(c);
	else
		ft_putchar_buf(c);
	if (info.modifiers & m_left_justified)
		ft_putnchar_buf(' ', info.min_width - 1);
}

void				display_escape(va_list arg, t_info info)
{
	(void)arg;
	putchar_padded('%', info);
}

void				display_char(va_list arg, t_info info)
{
	putchar_padded(va_arg(arg, int), info);
}

void				display_str(va_list arg, t_info info)
{
	void			*str;
	int				len;

	str = va_arg(arg, void*);
	if (str == NULL)
	{
		str = "(null)";
		info.input_len = l_none;
	}
	if (info.input_len == l_l)
		len = ft_wstrlen(str);
	else
		len = ft_strlen(str);
	if (info.precision >= 0)
		len = MIN(len, info.precision);
	if (!(info.modifiers & m_left_justified))
		ft_putnchar_buf(getc(info), info.min_width - len);
	if (info.input_len == l_l)
		ft_putnwstr_buf(str, len);
	else
		ft_putnstr_buf(str, len);
	if (info.modifiers & m_left_justified)
		ft_putnchar_buf(' ', info.min_width - len);
}
