/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/29 01:52:38 by lgarczyn         ###   ########.fr       */
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

int					disp_object(t_vm vm, char *file, char *ar, const char *cpu)
{
	u64				offset;
	t_cmd			*cmd;
	u32				i;
	static u64		last_vm;


	if (vm.mem.offset == last_vm)
		return (0);
	last_vm = vm.mem.offset;
	if (cpu)
		print("%s (architecture %s):\n", file, cpu);
	else if (ar)
		print("%s(%s):\n", ar, file);
	else
		print("%s:\n", file);
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
	if (out.data > mem.data + mem.size)
		out.size = 0;
	else if (out.data + out.size > mem.data + mem.size)
		out.size = (u64)(mem.data + mem.size - out.data);
	if (out.data + out.size > mem.data + mem.size)
		printerr("WTF");
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
		addr = sl(fat_64->offset, vm.is_swap);
		size = sl(fat_64->size, vm.is_swap);
		*cpu = fat_64->cputype;
	}
	else
	{
		fat_32 = (t_fat_arch*)ptr;
		addr = s(fat_32->offset, vm.is_swap);
		size = s(fat_32->size, vm.is_swap);
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

	i = 0;
	ptr = GET_CHECKED_PTR(sizeof(t_fat_header),
		vm.ncmds * (vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch)));
	while (i < vm.ncmds)
	{
		archmem = get_arch_map(vm, ptr, &cpu);
		//print("%llu\n", archmem.offset);
		CHECK(get_vm(&archvm, archmem, vm.target));
		CHECK(archvm.type == f_fat);
		CHECK(disp_object(archvm, file, NULL,
			vm.ncmds == 1 ? NULL : get_cpu(cpu, vm.is_swap)));//CHECK IF NEEDED
		i++;
		ptr += vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	}
	return (0);
}

int					disp_file(t_mem mem, char *file, char *ar);

int					disp_ranlib(t_vm vm, char *file)
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
				info.name, file));
			i++;
			(void)file;
		}
	}
	else
		CHECK(disp_file(
				get_sub_mem(vm.mem, offset, vm.mem.size),
				vm.ar_info.name, file));
	return (0);
}

int					disp_file(t_mem mem, char *file, char *ar)
{
	t_vm			vm;
	t_target		target;

	target.segment = SEG_TEXT;
	target.section = SECT_TEXT;
	target.display = &putdata;
	CHECK(get_vm(&vm, mem, target));
	if (vm.type == f_fat)
		CHECK(disp_fat(vm, file));
	else if (vm.type == f_ranlib)
		CHECK(disp_ranlib(vm, file));
	else
		CHECK(disp_object(vm, file, ar, NULL));
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
		CHECK(disp_file(mem, argv[i], NULL));
		munmap(mem.data, mem.size);
	}
	ft_flush_buf();
	return (errno);
}
