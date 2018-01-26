/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 06:57:37 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 22:06:14 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stddef.h>

static t_arg		g_args[] =
{
	{'s', display_str, {m_none, -1, -1, l_none, -1}},
	{'c', display_char, {m_none, -1, -1, l_none, -1}},

	{'d', display_int, {m_none, -1, -1, l_none, 10}},
	{'i', display_int, {m_none, -1, -1, l_none, 10}},
	{'o', display_int, {m_unsigned, -1, -1, l_none, 8}},
	{'u', display_int, {m_unsigned, -1, -1, l_none, 10}},
	{'x', display_int, {m_unsigned, -1, -1, l_none, 16}},
	{'X', display_int, {m_unsigned | m_uppercase, -1, -1, l_none, 16}},

	{'p', display_int,
		{m_unsigned | m_verbose | m_always_verbose, -1, -1, l_t, 16}},

	{'C', display_char, {m_none, -1, -1, l_l, -1}},
	{'S', display_str, {m_none, -1, -1, l_l, -1}},

	{'O', display_int, {m_unsigned, -1, -1, l_l, 8}},
	{'D', display_int, {m_none, -1, -1, l_l, 10}},
	{'U', display_int, {m_unsigned, -1, -1, l_l, 10}},

	{'%', display_escape, {m_none, -1, -1, l_none, -1}},

	{'b', display_int, {m_unsigned, -1, -1, l_none, 2}},
	{'B', display_int, {m_unsigned, -1, -1, l_l, 2}},
};

intmax_t			get_int_arg(va_list arg, t_length l)
{
	if (l == l_hh)
		return (intmax_t)(char)(va_arg(arg, int));
	if (l == l_h)
		return (intmax_t)(short)(va_arg(arg, int));
	if (l == l_none)
		return (va_arg(arg, int));
	if (l == l_l)
		return (va_arg(arg, long int));
	if (l == l_ll)
		return (va_arg(arg, long long int));
	if (l == l_j)
		return (va_arg(arg, intmax_t));
	if (l == l_z)
		return (va_arg(arg, size_t));
	if (l == l_t)
		return (va_arg(arg, ptrdiff_t));
	return (0);
}

uintmax_t			get_u32_arg(va_list arg, t_length l)
{
	if (l == l_hh)
		return (uintmax_t)(unsigned char)(va_arg(arg, unsigned int));
	if (l == l_h)
		return (uintmax_t)(unsigned short)(va_arg(arg, unsigned int));
	if (l == l_none)
		return (va_arg(arg, unsigned int));
	if (l == l_l)
		return (va_arg(arg, unsigned long int));
	if (l == l_ll)
		return (va_arg(arg, unsigned long long int));
	if (l == l_j)
		return (va_arg(arg, uintmax_t));
	if (l == l_z)
		return (va_arg(arg, size_t));
	if (l == l_t)
		return (va_arg(arg, ptrdiff_t));
	return (0);
}

void				display(char format, t_info info, va_list list)
{
	size_t			i;
	t_info			def;

	i = 0;
	while (i < sizeof(g_args) / sizeof(t_arg))
	{
		if (format == g_args[i].name)
		{
			def = g_args[i].info;
			info.modifiers |= def.modifiers;
			if (def.input_len != l_none)
				info.input_len = def.input_len;
			info.base = def.base;
			g_args[i].callback(list, info);
			return ;
		}
		i++;
	}
	putchar_padded(format, info);
}
