/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:44:27 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 09:36:31 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <sys/types.h>
#include <sys/sysctl.h>

int					disp_sections(t_vm vm, u64 offset, u64 n)
{
	t_section_64	sec;
	u64				i;

	i = 0;
	CHECK_LEN(offset +
		n * (vm.is_64 ? sizeof(t_section_64) : sizeof(t_section_32)));
	while (i < n)
	{
		sec = read_section(&vm.mem.data[offset], vm.is_swap, vm.is_64);
		sect_type_push(vm.sect_types, sec.sectname);
		if (vm.target.is_otool &&
			ft_strcmp(sec.sectname, vm.target.section) == 0 &&
			ft_strcmp(sec.segname, vm.target.segment) == 0)
		{
			print("Contents of (%s,%s) section\n",
				vm.target.segment, vm.target.section);
			CHECK_LEN(sec.offset + sec.size);
			vm.target.display(&vm, &vm.mem.data[sec.offset],
				sec.size, sec.addr);
		}
		offset += vm.is_64 ? sizeof(t_section_64) : sizeof(t_section_32);
		i++;
	}
	return (0);
}

int					disp_segment(t_vm vm, u64 offset, u32 *sect_size)
{
	t_seg_cmd_64	seg;
	t_symtab_cmd	sym;
	t_load_cmd		*c;

	CHECK_LEN(offset + sizeof(t_load_cmd));
	c = (t_load_cmd*)(vm.mem.data + offset);
	CHECK(c->cmdsize == 0);
	*sect_size = c->cmdsize;
	swap_load(c, vm.is_swap);
	if (c->cmd == LC_SEGMENT_64 || c->cmd == LC_SEGMENT)
	{
		offset += vm.is_64 ? sizeof(t_seg_cmd_64) : sizeof(t_seg_cmd_32);
		CHECK_LEN(offset);
		seg = read_segment(c, vm.is_swap, vm.is_64);
		CHECK(disp_sections(vm, offset, seg.nsects));
	}
	else if (vm.target.is_otool == false && c->cmd == LC_SYMTAB)
	{
		CHECK_LEN(offset + sizeof(t_symtab_cmd));
		sym = read_symtab_cmd(c, vm.is_swap);
		CHECK(store_symtab(vm, sym, vm.sym_tokens));
	}
	return (0);
}

int					disp_object(t_vm vm, char *file, char *ar, bool disp_cpu)
{
	u64				offset;
	u32				i;
	t_sect_types	sect_types;
	t_array			sym_tokens;
	u32				sect_size;

	vm.sect_types = &sect_types;
	vm.sym_tokens = &sym_tokens;
	bzero(&sect_types, sizeof(t_sect_types));
	bzero(&sym_tokens, sizeof(t_array));
	if (disp_cpu)
		print("%s (architecture %s):\n", file, get_cpu(vm.cpu));
	else if (ar)
		print("%s(%s):\n", ar, file);
	else if (vm.target.disp_names)
		print("%s%s:\n", vm.target.is_otool ? "" : "\n", file);
	offset = vm.is_64 ? sizeof(t_mach_header_64) : sizeof(t_mach_header);
	i = 0;
	while (i++ < vm.ncmds)
	{
		CHECK(disp_segment(vm, offset, &sect_size));
		offset += sect_size;
	}
	disp_symtab(vm, &sym_tokens, &sect_types);
	return (0);
}

int					disp_fat(t_vm vm, char *file, bool all)
{
	u32				i;
	t_vm			archvm;
	t_mem			archmem;
	void			*ptr;
	cpu_type_t		cpu;

	i = -1;
	ptr = GET_CHECKED_PTR(sizeof(t_fat_header),
		vm.ncmds * (vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch)));
	while (++i < vm.ncmds)
	{
		archmem = get_arch_map(vm, ptr, &cpu);
		if ((~CPU_ARCH_MASK & cpu) == get_cpu_type() + 1 || all)
		{
			CHECK(get_vm(&archvm, archmem, vm.target));
			CHECK(disp_object(archvm, file, NULL, vm.ncmds > 1 && all));
			if (all == false)
				return (0);
		}
		ptr += vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	}
	if (all == false)
		return (disp_fat(vm, file, true));
	return (0);
}

int					disp_file(t_mem mem, t_target target, char *file, char *ar)
{
	t_vm			vm;

	CHECK(get_vm(&vm, mem, target));
	if (vm.type == f_fat)
		CHECK(disp_fat(vm, file, false));
	else if (vm.type == f_ranlib)
		CHECK(disp_ranlib(vm, file));
	else
		CHECK(disp_object(vm, file, ar, false));
	return (0);
}
