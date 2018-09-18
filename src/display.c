/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:44:27 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 18:12:34 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				disp_header(t_mach_header *p, bool is_swap)
{
	t_mach_header	h;

	h.magic = s(p->magic, is_swap);
	h.cputype = s(p->cputype, is_swap);
	h.cpusubtype = s(p->cpusubtype, is_swap);
	h.filetype = s(p->filetype, is_swap);
	h.ncmds = s(p->ncmds, is_swap);
	h.sizeofcmds = s(p->sizeofcmds, is_swap);
	h.flags = s(p->flags, is_swap);
	CPU_ARCH_ABI64;
	print("Mach header\n");
	print("      magic cputype cpusubtype  caps");
	print("    filetype ncmds sizeofcmds      flags\n");
	print(" 0x%.8x %7u %10u  0x%.2x %11u %5u %10u 0x%5.8X\n",
		h.magic, h.cputype, h.cpusubtype & ~CPU_SUBTYPE_MASK,
		(h.cpusubtype >> 24) & 0xFF,
		h.filetype, h.ncmds, h.sizeofcmds, h.flags);
}

void				disp_filename(t_vm vm, char *file, char *ar)
{
	if (vm.target.show_cpu)
		print("%s%s (%sarchitecture %s):\n",
			vm.target.is_otool ? "" : "\n",
			file,
			vm.target.is_otool ? "" : "for ", get_cpu(vm.cpu));
	else if (ar)
		print("%s%s(%s):\n", vm.target.is_otool ? "" : "\n", ar, file);
	else if (vm.target.show_names)
		print("%s%s:\n", vm.target.is_otool ? "" : "\n", file);
}

void				disp_data(t_vm *vm, u8 *data, size_t size, size_t addr)
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
