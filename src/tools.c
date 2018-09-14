/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:02:52 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 01:10:53 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <fcntl.h>
#include <unistd.h>

int					array_push(t_array *array, void *data, size_t size)
{
	size_t			new_pos;

	new_pos = array->pos + size;
	if (new_pos > array->size)
	{
		CHECK(ft_realloc(&array->data, array->size, new_pos * 2));
		array->size = new_pos * 2;
	}
	ft_memcpy(array->data + array->pos, data, size);
	array->pos = new_pos;
	return (0);
}

int				check_string(t_vm vm, u8 *str)
{
	size_t		x;

	x = 0;
	while (1)
	{
		if (str >= vm.mem.file + vm.mem.size || str < vm.mem.file)
		{
			printerr("bad string %p after %i\n", str - (u64)vm.mem.file, x);
			return (EINVAL);
		}
		if (*str == 0)
			return (0);
		str++;
		x++;
	}
}
