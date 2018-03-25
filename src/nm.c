/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/25 20:52:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

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
		if (ft_strcmp(sec.sectname, vm.target.section) == 0 &&
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

int					disp_segment(t_vm vm, t_cmd *c, u64 offset)
{
	t_seg_cmd_64	seg;

	CHECK_LEN(offset + sizeof(c->cmd));
	if (c->cmd == LC_SEGMENT_64 || c->cmd == LC_SEGMENT)
	{
		offset += vm.is_64 ? sizeof(c->seg64) : sizeof(c->seg32);
		CHECK_LEN(offset);
		seg = read_segment(c, vm.is_swap, vm.is_64);
		CHECK(disp_sections(vm, offset, seg.nsects));
	}
	return (0);
}

int					disp_object(t_vm vm, char *file, const char *cpu)
{
	u64				offset;
	t_cmd			*cmd;
	u32				i;

	if (cpu == NULL)
		print("%s:\n", file);
	else
		print("%s (architecture %s):\n", file, cpu);
	offset = vm.is_64 ? sizeof(t_mach_header_64) : sizeof(t_mach_header);
	i = 0;
	while (i++ < vm.ncmds)
	{
		CHECK_LEN(offset + sizeof(t_load_command));
		cmd = (t_cmd*)(vm.mem.data + offset);
		swap_load(&cmd->load, vm.is_swap);
		CHECK(disp_segment(vm, cmd, offset));
		offset += cmd->load.cmdsize;
	}
	return (0);
}

t_mem				get_sub_mem(t_mem mem, u64 offset, u64 size)
{
	t_mem			out;

	out.file = mem.file;
	out.offset = mem.offset + offset;
	out.data = mem.data + offset;
	out.size = size;

	if (out.file + out.offset != out.data)
	{
		printerr("WTF\n");
		print("WTF\n");
	}
	return (out);
}

t_mem				get_arch_map(t_vm vm, void *ptr, cpu_type_t *cpu)
{
	u64				addr;
	u64				size;
	t_fat_arch		*fat_32;
	t_fat_arch_64	*fat_64;

	if (vm.is_64)
	{
		fat_64 = (t_fat_arch_64*)ptr;
		addr = sl(vm.is_swap, fat_64->offset);
		size = sl(vm.is_swap, fat_64->size);
		*cpu = fat_64->cputype;
	}
	else
	{
		fat_32 = (t_fat_arch*)ptr;
		addr = s(vm.is_swap, fat_32->offset);
		size = s(vm.is_swap, fat_32->size);
		*cpu = fat_32->cputype;
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

	CHECK_LEN((u64)sizeof(t_fat_header) +
		vm.ncmds * (vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch)));
	i = 0;
	ptr = vm.mem.data + sizeof(t_fat_header);
	while (i < vm.ncmds)
	{
		archmem = get_arch_map(vm, ptr, &cpu);
		CHECK_LEN((archmem.data - vm.mem.data) + archmem.size);
		archvm.ncmds = 0;
		CHECK(get_vm(&archvm, archmem));
		CHECK(archvm.type == f_fat);
		CHECK(disp_object(archvm, file, get_cpu(cpu, vm.is_swap)));
		i++;
		ptr += vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	}
	return (0);
}

int					disp_file(t_mem mem, char *file);

int					disp_ranlib(t_vm vm, char *file)
{
	u64				offset;
	u32				real_ncmds;
	t_symdef		*sym;
	u32				i;
	u64				name_len;
	char			*name;

	print("Archive : %s\n", file);
	offset = 8 + vm.ncmds;
	real_ncmds = s(GET_CHECKED_VAL(offset, u32) / 8, false);
	offset += sizeof(u32);
	sym = (t_symdef*)GET_CHECKED_PTR(offset, real_ncmds * sizeof(t_symdef));
	offset += real_ncmds * sizeof(t_symdef);
	name_len = GET_CHECKED_VAL(offset, u32);
	CHECK(GET_CHECKED_VAL(offset + name_len, u32) != 0);
	offset += sizeof(u32);
	i = 0;
	while (i < real_ncmds)
	{
		name = (char*)GET_CHECKED_PTR(offset + sym[i].name, name_len);
		//CHECK IF NULL TERMINATED
		print("%s(%s):\n", file, name);
		u64 len;
		CHECK(check_ranlib_header(vm, sym[i].object, &len));
		CHECK(disp_file(
			get_sub_mem(vm.mem, sym[i].object + len, vm.mem.size),
			name));
		i++;
		(void)file;
	}
	return (0);
}

int					disp_file(t_mem mem, char *file)
{
	t_vm			vm;

	CHECK(get_vm(&vm, mem));
	vm.target.segment = SEG_TEXT;
	vm.target.section = SECT_TEXT;
	vm.target.display = &putdata;
	if (vm.type == f_fat)
		CHECK(disp_fat(vm, file));
	else if (vm.type == f_ranlib)
		CHECK(disp_ranlib(vm, file));
	else
		CHECK(disp_object(vm, file, NULL));
	return (0);
}

int					main(int argc, char **argv)
{
	int				i;
	t_mem			mem;

	ft_buf(malloc(4096), 4096, 1);
	if (argc == 1)
	{
		argc = 2;
		argv[1] = "a.out";
	}
	i = 0;
	while (++i < argc)
	{
		mem = map(argv[i]);
		if (mem.data == NULL)
		{
			ft_perror_file_buf(argv[0], argv[i]);
			return (errno);
		}
		CHECK(disp_file(mem, argv[i]));
		munmap(mem.data, mem.size);
	}
	ft_flush_buf();
	return (errno);
}
