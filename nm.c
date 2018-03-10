/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/10 23:59:54 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int					disp_sections(t_vm vm, u64 offset, u64 n, u64 vmaddr)
{
	t_section_32	*sections_32;
	t_section_64	*sections_64;
	u64				i;
	char			*sec_name;
	u64				sec_size;

	i = 0;
	CHECK_LEN(offset +
		n * (vm.is_64 ? sizeof(t_section_64) : sizeof(t_section_32)));
	sections_64 = (t_section_64*)(vm.mem.data + offset);
	sections_32 = (t_section_32*)(vm.mem.data + offset);
	while (i < n)
	{
		sec_name = vm.is_64 ? sections_64[i].sectname : sections_32[i].sectname;
		offset = vm.is_64 ? sl(sections_64[i].addr, vm.is_swap) : s(sections_32[i].addr, vm.is_swap);
		sec_size = vm.is_64 ? sl(sections_64[i].size, vm.is_swap) : s(sections_32[i].size, vm.is_swap);
		if (strncmp(sec_name, SECT_TEXT, sizeof(SECT_TEXT)) == 0)
		{
			print("Contents of (__TEXT,__text) section\n");
			CHECK_LEN(offset - vmaddr + sec_size);
			(void)vmaddr;
			putdata(vm, &vm.mem.data[offset - vmaddr], sec_size, offset);
		}
		i++;
	}
	return (0);
}

int					disp_segment(t_vm vm, t_cmd *c, u64 offset)
{
	int				r;
	t_seg_cmd_64	seg;

	if (c->load.cmd == LC_SEGMENT_64 || c->load.cmd == LC_SEGMENT)
	{
		CHECK_LEN(offset + sizeof(c->name));
		if (ft_strncmp(c->name.segname, SEG_TEXT, sizeof(SEG_TEXT)) == 0)
		{
			offset += vm.is_64 ? sizeof(c->seg64) : sizeof(c->seg32);
			CHECK_LEN(offset);
			seg = read_segment(c, vm.is_swap, vm.is_64);
			r = disp_sections(vm, offset, seg.nsects, seg.vmaddr);
			if (r)
				return (r);
		}
	}
	return (0);
}

int					disp_segments(t_vm vm, char *file, const char *cpu)
{
	u64				offset;
	t_cmd			*cmd;
	u32				i;
	int				r;

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
		r = disp_segment(vm, cmd, offset);
		if (r)
			return (r);
		offset += cmd->load.cmdsize;
	}
	return (0);
}

t_mem				get_arch_map(t_vm vm, void *ptr, cpu_type_t *cpu)
{
	u64				addr;
	u64				size;
	t_mem			out;
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
	out.offset = addr;
	out.data = vm.mem.data + addr;
	out.size = size;
	return (out);
}

int					disp_archs(t_vm vm, char *file)
{
	int				r;
	u32				i;
	t_vm			archvm;
	t_mem			archmem;
	void			*ptr;

	cpu_type_t		fuck;

	CHECK_LEN((u64)sizeof(t_fat_header) +
		vm.ncmds * (vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch)));
	i = 0;
	ptr = vm.mem.data + sizeof(t_fat_header);
	while (i < vm.ncmds)
	{
		archmem = get_arch_map(vm, ptr, &fuck);
		CHECK_LEN((archmem.data - vm.mem.data) + archmem.size);
		archvm.ncmds = 0;
		r = get_vm(&archvm, archmem);
		if (r == 0 && archvm.type == f_fat)
			r = 1000;
		if (r == 0)
			r = disp_segments(archvm, file, get_cpu(fuck, vm.is_swap));
		if (r)
			return (r);
		i++;
		ptr += vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	}
	return (0);
}

int				disp_file(t_mem mem, char *file)
{
	int				r;
	t_vm			vm;

	r = 0;
	r = get_vm(&vm, mem);
	if (r)
		return (r);
	if (vm.type == f_fat)
		r = disp_archs(vm, file);
	else
		r = disp_segments(vm, file, NULL);
	return r;
}

int					main(int argc, char **argv)
{
	int				i;
	int				r;
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
		r = disp_file(mem, argv[i]);
		if (r)
			print("fuck %s: %i\n", argv[i], r);
		munmap(mem.data, mem.size);
	}
	ft_flush_buf();
	return (errno);
}
