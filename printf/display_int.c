/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 06:57:48 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/08/10 06:57:49 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdarg.h>

static void			display_final(char *header, char *number, t_info info)
{
	t_bool			zero_padded;
	t_bool			left_justified;
	int				padding;
	int				spacing;
	int				num_len;

	zero_padded = (m_zero_padded & info.modifiers) && (info.precision == -1);
	if (info.precision == -1)
		info.precision = 1;
	num_len = ft_strlen(number);
	padding = MAX(info.precision - num_len, 0);
	spacing = MAX(info.min_width - (padding + ft_strlen(header) + num_len), 0);
	left_justified = m_left_justified & info.modifiers;
	if (!zero_padded && !left_justified)
		ft_putnchar_buf(' ', spacing);
	ft_putstr_buf(header);
	if (zero_padded && !left_justified)
		ft_putnchar_buf('0', padding + spacing);
	else
		ft_putnchar_buf('0', padding);
	ft_putrstr_buf(number);
	if (left_justified)
		ft_putnchar_buf(' ', spacing);
}

static void			fill_uint(char *buf, uintmax_t n, t_info info)
{
	static char		dicl[] = "0123456789abcdef";
	static char		dicu[] = "0123456789ABCDEF";
	uintmax_t		mod;
	t_bool			uppercase;

	uppercase = info.modifiers & m_uppercase;
	while (n > 0)
	{
		mod = n % info.base;
		n /= info.base;
		*buf = uppercase ? dicu[mod] : dicl[mod];
		buf++;
	}
	*buf = '\0';
}

static void			*get_header(t_info info, int sign)
{
	if ((info.modifiers & m_verbose) &&
		(info.modifiers & m_always_verbose || sign != 0))
	{
		if (info.base == 16)
			if (info.modifiers & m_uppercase)
				return ("0X");
			else
				return ("0x");
		else
			return ("0");
	}
	if (info.base == 8
		&& info.precision == 0
		&& sign == 0
		&& info.modifiers & m_verbose)
		return ("0");
	if (info.modifiers & m_unsigned)
		return ("");
	if (sign < 0)
		return ("-");
	if (info.modifiers & m_always_signed)
		return ("+");
	if (info.modifiers & m_plus_is_space)
		return (" ");
	return ("");
}

void				display_int(va_list arg, t_info info)
{
	char			numbuf[(sizeof(uintmax_t) + 1) * 8];
	char			*header;
	intmax_t		num;
	uintmax_t		unum;
	int				sign;

	if (info.modifiers & m_unsigned)
	{
		unum = get_uint_arg(arg, info.input_len);
		sign = unum > 0;
	}
	else
	{
		num = get_int_arg(arg, info.input_len);
		sign = CLAMP(num, -1, 1);
		unum = (num >= 0) ? (uintmax_t)num : -((uintmax_t)num);
	}
	header = get_header(info, sign);
	fill_uint(numbuf, unum, info);
	display_final(header, numbuf, info);
}
