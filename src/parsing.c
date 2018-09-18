/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:44:27 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 18:12:34 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <sys/types.h>
#include <sys/sysctl.h>

int					disp_sections(t_vm vm, u64 offset, u64 n)
{
	t_section_64	sec;
	u64				i;
	char			t;

	CHECK_LEN(offset +
		n * (vm.is_64 ? sizeof(t_section_64) : sizeof(t_section_32)));
	i = -1;
	while (++i < n)
	{
		sec = read_section(&vm.mem.data[offset], vm.is_swap, vm.is_64);
		t = get_sect_type(sec.sectname);
		array_push(vm.sect_types, &t, sizeof(char));
		if (filter_disp(vm.target, sec))
		{
			print("Contents of (%s,%s) section\n",
				sec.segname, sec.sectname);
			CHECK_LEN(sec.offset + sec.size);
			disp_data(&vm, &vm.mem.data[sec.offset],
				sec.size, sec.addr);
		}
		offset += vm.is_64 ? sizeof(t_section_64) : sizeof(t_section_32);
	}
	return (OK);
}

int					disp_segment(t_vm vm, u64 offset, u32 *sect_size)
{
	t_seg_cmd_64	seg;
	t_symtab_cmd	sym;
	t_load_cmd		c;
	t_load_cmd		*cmd;

	cmd = (t_load_cmd*)GET_CHECKED_PTR(offset, sizeof(t_load_cmd));
	c = read_load(cmd, vm.is_swap);
	CHECK(c.cmdsize == 0);
	*sect_size = c.cmdsize;
	if (c.cmd == LC_SEGMENT_64 || c.cmd == LC_SEGMENT)
	{
		offset += vm.is_64 ? sizeof(t_seg_cmd_64) : sizeof(t_seg_cmd_32);
		CHECK_LEN(offset);
		seg = read_segment(cmd, vm.is_swap, vm.is_64);
		CHECK(disp_sections(vm, offset, seg.nsects));
	}
	else if (vm.target.is_otool == false && c.cmd == LC_SYMTAB)
	{
		CHECK_LEN(offset + sizeof(t_symtab_cmd));
		sym = read_symtab_cmd(cmd, vm.is_swap);
		CHECK(store_symtab(vm, sym, vm.sym_tokens));
	}
	return (OK);
}

int					disp_object(t_vm vm, char *file, char *ar)
{
	u64				offset;
	u32				i;
	t_array			sect_types;
	t_array			sym_tokens;
	u32				sect_size;

	ft_bzero(&sect_types, sizeof(t_array));
	ft_bzero(&sym_tokens, sizeof(t_array));
	vm.sect_types = &sect_types;
	vm.sym_tokens = &sym_tokens;
	offset = vm.is_64 ? sizeof(t_mach_header_64) : sizeof(t_mach_header);
	i = 0;
	disp_filename(vm, file, ar);
	while (i++ < vm.ncmds)
	{
		if (disp_segment(vm, offset, &sect_size))
		{
			free_arrays(&vm);
			return (1);
		}
		offset += sect_size;
	}
	disp_symtab(vm, vm.sym_tokens, vm.sect_types);
	free_arrays(&vm);
	return (OK);
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
	vm.target.show_cpu = vm.ncmds > 1 && all;
	while (++i < vm.ncmds)
	{
		archmem = get_arch_map(vm, ptr, &cpu);
		if (cpu == 0x1000007 || all)
		{
			CHECK(get_vm(&archvm, archmem, vm.target));
			CHECK(disp_object(archvm, file, NULL));
			if (all == false)
				return (OK);
		}
		ptr += vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	}
	if (all == false)
		return (disp_fat(vm, file, true));
	return (OK);
}

int					disp_file(t_mem mem, t_target target, char *file, char *ar)
{
	t_vm			vm;
	int				err;

	target.show_cpu = false;
	CHECK(get_vm(&vm, mem, target));
	if (vm.type == f_fat)
		err = disp_fat(vm, file, false);
	else if (vm.type == f_ranlib)
		err = disp_ranlib(vm, file);
	else
		err = disp_object(vm, file, ar);
	CHECK(err);
	return (OK);
}
