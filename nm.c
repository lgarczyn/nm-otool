/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/09 04:10:39 by lgarczyn         ###   ########.fr       */
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
		offset = vm.is_64 ? sections_64[i].offset : sections_32[i].offset;
		sec_size = vm.is_64 ? sections_64[i].size : sections_32[i].size;
		if (strncmp(sec_name, SECT_TEXT, sizeof(SECT_TEXT)) == 0)
		{
			printf("Contents of (__TEXT,__text) section\n");
			CHECK_LEN(offset + sec_size);
			putdata(vm.mem.data, offset, sec_size, vmaddr);
		}
		i++;
	}
	return (0);
}

int					disp_segment(t_vm vm, t_cmd *c, u64 offset)
{
	int				r;

	if (c->load.cmd == LC_SEGMENT_64 || c->load.cmd == LC_SEGMENT)
	{
		CHECK_LEN(offset + sizeof(c->name));
		if (ft_strncmp(c->name.segname, SEG_TEXT, sizeof(SEG_TEXT)) == 0)
		{
			offset += vm.is_64 ? sizeof(c->seg64) : sizeof(c->seg32);
			CHECK_LEN(offset);
			if (vm.is_64)
			{
				swap_segment_64(&c->seg64, vm.is_swap);
				r = disp_sections(vm, offset, c->seg64.nsects, c->seg64.vmaddr);
			}
			else
			{
				swap_segment_32(&c->seg32, vm.is_swap);
				r = disp_sections(vm, offset, c->seg32.nsects, c->seg32.vmaddr);
			}
			if (r)
				return (r);
		}
	}
	return (0);
}

int					disp_segments(t_vm vm, char *file)
{
	u64				offset;
	t_cmd			*cmd;
	u32				i;
	int				r;

	if (vm.mem.addr == 0)
		printf("%s:\n", file);
	else
		printf("%s (architecture %s):\n", file, vm.cpu);
	offset = vm.mem.addr +
		(vm.is_64 ? sizeof(t_mach_header_64) : sizeof(t_mach_header));
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

t_mem				get_arch_map(t_vm vm, void *ptr)
{
	t_mem			out;
	t_fat_arch		*fat_32;
	t_fat_arch_64	*fat_64;

	out.data = vm.mem.data;
	if (vm.is_64)
	{
		fat_64 = (t_fat_arch_64*)ptr;
		out.addr = vm.is_swap ? swap(fat_64->offset) : fat_64->offset;
		out.size = vm.is_swap ? swap(fat_64->size) : fat_64->size;
	}
	else
	{
		fat_32 = (t_fat_arch*)ptr;
		out.addr = vm.is_swap ? swap(fat_32->offset) : fat_32->offset;
		out.size = vm.is_swap ? swap(fat_32->size) : fat_32->size;
	}
	return (out);
}

int					disp_archs(t_vm vm, char *file)
{
	int				r;
	u32				i;
	t_vm			archvm;
	t_mem			archmem;
	void			*ptr;

	CHECK_LEN(sizeof(t_fat_header) +
		vm.ncmds * vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch));
	i = 0;
	ptr = vm.mem.data + sizeof(t_fat_header);
	while (i < vm.ncmds)
	{
		archmem = get_arch_map(vm, ptr);
		CHECK_LEN(archmem.addr + archmem.size);
		r = get_vm(&archvm, archmem);
		if (r == 0 && archvm.is_fat)
			r = 1000;
		if (r == 0)
			r = disp_segments(archvm, file);
		if (r)
			return (r);
		i++;
		ptr += vm.is_64 ? sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	}
	return (0);
}

void				disp_file(char *prog, char *file)
{
	int				r;
	t_vm			vm;
	t_mem			mem;

	printf("%s\n", file);
	r = 0;
	mem = map(file);
	if (mem.data == NULL)
		r = 1;
	printf("%s\n", file);
		
	if (r == 0)
		r = get_vm(&vm, mem);
	printf("%s\n", file);
	if (r == 0)
	{
		if (vm.is_fat)
			r = disp_archs(vm, file);
		else
			r = disp_segments(vm, file);
	}
	printf("%s\n", file);
	if (r == 1)
		ft_perror_file_buf(prog, file);
	else if (r > 1)
		printf("fuck %s: %i\n", file, r);
	printf("%s\n", file);
	if (mem.data != NULL)
		munmap(mem.data, mem.size);
}

int					main(int argc, char **argv)
{
	int				i;

	ft_buf(malloc(4096), 4096, 1);
	if (argc == 1)
	{
		argc = 2;
		argv[1] = "a.out";
	}
	i = 0;
	while (++i < argc)
	{
		disp_file(argv[0], argv[1]);
	}
	ft_flush_buf();
	return (errno);
}
