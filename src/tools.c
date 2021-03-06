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
#include <sys/sysctl.h>

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
	return (OK);
}

void				free_arrays(t_vm *vm)
{
	free(vm->sect_types->data);
	free(vm->sym_tokens->data);
	vm->sect_types = NULL;
	vm->sym_tokens = NULL;
}

int					check_string(t_vm vm, u8 *str)
{
	size_t			x;

	x = 0;
	while (1)
	{
		if (str >= vm.mem.file + vm.mem.offset + vm.mem.size ||
			str < vm.mem.file)
		{
			printerr("bad string %p after %i\n", str - (u64)vm.mem.file, x);
			return (ERR_MEM);
		}
		if (*str == 0)
			return (OK);
		str++;
		x++;
	}
}

t_mem				get_sub_mem(t_mem mem, u64 offset, u64 size)
{
	t_mem			out;

	out.file = mem.file;
	out.offset = mem.offset + offset;
	out.data = mem.data + offset;
	out.size = size;
	if (out.data > mem.data + mem.size)
		out.size = 0;
	else if (out.data + out.size > mem.data + mem.size)
		out.size = (u64)(mem.data + mem.size - out.data);
	return (out);
}

int					gen_filter(int r, char *p, char *f)
{
	if (r == 1)
		return (1);
	if (r == ERR_MEM)
	{
		printerr("%s: %s: truncated or malformed object.\n", p, f);
		return (1);
	}
	if (r)
	{
		printerr("%s: %s: %s.\n", p, f, ft_strerror(r));
	}
	return (r);
}
