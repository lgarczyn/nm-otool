/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:32 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 01:25:45 by lgarczyn         ###   ########.fr       */
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

int					main(int argc, char **argv)
{
	int				i;
	t_mem			mem;
	t_target		target;

	target.segment = SEG_TEXT;
	target.section = SECT_TEXT;
	target.display = &putdata;
	target.is_otool = true;
	ft_buf(malloc(4096), 4096, 1);
	if (argc == 1)
	{
		argc = 2;
		argv[1] = "a.out";
	}
	target.disp_names = true;
	i = 0;
	while (++i < argc)
	{
		CHECK_SKIP(argv[i], map(&mem, argv[i]));
		CHECK_DISP(argv[i], disp_file(mem, target, argv[i], NULL));
		munmap(mem.data, mem.size);
	}
	ft_flush_buf();
	return (errno);
}


