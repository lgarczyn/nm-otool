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

int					disp_sections(t_vm vm, u64 offset, u64 n, t_sect_types *buffer)
{
	t_section_64	sec;
	u64				i;

	i = 0;
	CHECK_LEN(offset +
		n * (vm.is_64 ? sizeof(t_section_64) : sizeof(t_section_32)));
	while (i < n)
	{
		sec = read_section(&vm.mem.data[offset], vm.is_swap, vm.is_64);
		buffer->data[(buffer->pos)++] = get_sect_type(sec.sectname);
		if (vm.target.is_otool &&
			ft_strcmp(sec.sectname, vm.target.section) == 0 &&
			ft_strcmp(sec.segname, vm.target.segment) == 0)
		{
			print("Contents of (%s,%s) section\n",
				vm.target.segment, vm.target.section);
			CHECK_LEN(sec.offset + sec.size);
			vm.target.display(&vm, &vm.mem.data[sec.offset], sec.size, sec.addr);
		}

		offset += vm.is_64 ? sizeof(t_section_64) : sizeof(t_section_32);
		i++;
	}
	return (0);
}

int					disp_segment(t_vm vm, t_cmd *c, u64 offset,
	t_sect_types *buffer, t_array *tokens)
{
	t_seg_cmd_64	seg;
	t_symtab_cmd	sym;

	CHECK_LEN(offset + sizeof(c->cmd));
	if (c->cmd == LC_SEGMENT_64 || c->cmd == LC_SEGMENT)
	{
		offset += vm.is_64 ? sizeof(c->seg64) : sizeof(c->seg32);
		CHECK_LEN(offset);
		seg = read_segment(c, vm.is_swap, vm.is_64);
		CHECK(disp_sections(vm, offset, seg.nsects, buffer));
	}
	if (vm.target.is_otool == false)
	{
		if (c->cmd == LC_SYMTAB)
		{
			offset += sizeof(t_symtab_cmd);
			CHECK_LEN(offset);
			sym = read_symtab_cmd(c, vm.is_swap);
			CHECK(store_symtab(vm, sym, tokens));
		}
	}
	return (0);
}

int					disp_object(t_vm vm, char *file, char *ar, bool disp_cpu)
{
	u64				offset;
	t_cmd			*cmd;
	u32				i;
	t_sect_types	buffer;
	t_array			tokens;

	if (disp_cpu)
		print("%s (architecture %s):\n", file, get_cpu(vm.cpu));
	else if (ar)
		print("%s(%s):\n", ar, file);
	else if (vm.target.disp_names && vm.target.is_otool == false)
		print("\n%s:\n", file);
	else if (vm.target.disp_names)
		print("%s:\n", file);
	offset = vm.is_64 ? sizeof(t_mach_header_64) : sizeof(t_mach_header);
	i = 0;
	bzero(&buffer, sizeof(t_sect_types));
	bzero(&tokens, sizeof(t_array));
	while (i++ < vm.ncmds)
	{
		CHECK_LEN(offset + sizeof(t_load_cmd));
		cmd = (t_cmd*)(vm.mem.data + offset);
		swap_load(&cmd->load, vm.is_swap);
		CHECK(disp_segment(vm, cmd, offset, &buffer, &tokens));
		CHECK(cmd->load.cmdsize == 0);
		offset += cmd->load.cmdsize;
	}
	disp_symtab(vm, &tokens, &buffer);
	return (0);
}

t_mem				get_arch_map(t_vm vm, void *ptr, cpu_type_t *cpu)
{
	u64				addr;
	u64				size;
	t_fat_arch		*fat_32;
	t_fat_arch_64	*fat_64;

	fat_32 = (t_fat_arch*)ptr;
	fat_64 = (t_fat_arch_64*)ptr;
	*cpu = s(fat_32->cputype, vm.is_swap);
	if (vm.is_64)
	{
		addr = sl(fat_64->offset, vm.is_swap);
		size = sl(fat_64->size, vm.is_swap);
	}
	else
	{
		addr = s(fat_32->offset, vm.is_swap);
		size = s(fat_32->size, vm.is_swap);
	}
	return (get_sub_mem(vm.mem, addr, size));
}

int					disp_fat(t_vm vm, char *file)
{
	u32				i;
	t_vm			archvm;
	t_mem			archmem;
	void			*ptr;
	cpu_type_t		cpu;

	i = 0;
	ptr = GET_CHECKED_PTR(sizeof(t_fat_header),
		vm.ncmds * (vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch)));
	while (i < vm.ncmds)
	{
		archmem = get_arch_map(vm, ptr, &cpu);
		CHECK(get_vm(&archvm, archmem, vm.target));
		CHECK(archvm.type == f_fat);
		CHECK(disp_object(archvm, file, NULL, vm.ncmds > 1));
		i++;
		ptr += vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	}
	return (0);
}

int					disp_ranlib(t_vm vm, t_target target, char *file)
{
	u64				offset;
	t_symdef		*sym;
	u32				i;
	t_ar_info		info;

	offset = 8 + vm.ar_info.header_len;
	print("Archive : %s\n", file);
	if (ft_strcmp(vm.ar_info.name, "__.SYMDEF") == 0 ||
		ft_strcmp(vm.ar_info.name, "__.SYMDEF SORTED") == 0)
	{
		sym = (t_symdef*)GET_CHECKED_PTR(offset + sizeof(u32),
			vm.ar_info.ncmds * sizeof(t_symdef));
		i = 0;
		while (i < vm.ar_info.ncmds)
		{
			CHECK(check_ranlib_header(vm, sym[i].object, &info));
			CHECK(disp_file(
				get_sub_mem(vm.mem, sym[i].object + info.header_len, vm.mem.size),
				target, info.name, file));
			i++;
			(void)file;
		}
	}
	else
		CHECK(disp_file(
				get_sub_mem(vm.mem, offset, vm.mem.size),
				target, vm.ar_info.name, file));
	return (0);
}

int					disp_file(t_mem mem, t_target target, char *file, char *ar)
{
	t_vm			vm;

	CHECK(get_vm(&vm, mem, target));
	if (vm.type == f_fat)
		CHECK(disp_fat(vm, file));
	else if (vm.type == f_ranlib)
		CHECK(disp_ranlib(vm, target, file));
	else
		CHECK(disp_object(vm, file, ar, false));
	return (0);
}
