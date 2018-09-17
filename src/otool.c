/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:32 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 18:12:54 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static void			putdata(t_vm *vm, u8 *data, size_t size, size_t addr)
{
	size_t			i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0 && vm->is_64)
			print("%016lx\t", addr + i);
		else if (i % 16 == 0)
			print("%08lx\t", addr + i);
		if (vm->is_swap && i % 4 != 3)
			print("%02x", data[i]);
		else
			print("%02x ", data[i]);
		if (i % 16 == 15)
			print("\n");
		i++;
	}
	if (i % 16 != 0)
		print("\n");
}

static int			otool_filter(char *p, char *file, int r)
{
	if (r == 1)
		return (1);
	if (r == ERR_MAGIC)
	{
		print("%s: is not an object file\n", file);
		return (1);
	}
	return (gen_filter(r, p, file));
}

static t_target		get_otool_target(void)
{
	t_target		target;

	target.segment = SEG_TEXT;
	target.section = SECT_TEXT;
	target.display = &putdata;
	target.disp_names = true;
	target.is_otool = true;
	return (target);
}

int					main(int argc, char **argv)
{
	int				i;
	t_mem			mem;
	t_target		target;

	target = get_otool_target();
	ft_buf(malloc(4096), 4096, 1);
	if (argc == 1)
	{
		argc = 2;
		argv[1] = "a.out";
	}
	i = 0;
	while (++i < argc)
	{
		if (otool_filter(argv[0], argv[i], map(&mem, argv[i])))
			return (1);
		if (otool_filter(argv[0], argv[i], disp_file(mem, target, argv[i], 0)))
			return (1);
		if (otool_filter(argv[0], argv[1], munmap(mem.data, mem.size)))
			return (1);
	}
	ft_flush_buf();
	return (OK);
}
