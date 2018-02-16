/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/16 02:56:17 by lgarczyn         ###   ########.fr       */
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
		/*printf("--------------\nsection %llu\n--------------\n", i);
		if (vm.is_64)
		{
			printf("sectname 	%s\n", sections_64->sectname);
			printf("segname 	%s\n", sections_64->segname);
			printf("addr 	%llu\n", sl(sections_64->addr, vm.is_swap));
			printf("size 	%llu\n", sl(sections_64->size, vm.is_swap));
			printf("offset 	%u\n", s(sections_64->offset, vm.is_swap));
			printf("align 	%u\n", s(sections_64->align, vm.is_swap));
			printf("reloff 	%u\n", s(sections_64->reloff, vm.is_swap));
			printf("nreloc 	%u\n", s(sections_64->nreloc, vm.is_swap));
			printf("flags 	%u\n", s(sections_64->flags, vm.is_swap));
			printf("reserved 	%u\n", s(sections_64->reserved1, vm.is_swap));
			printf("reserved 	%u\n", s(sections_64->reserved2, vm.is_swap));
			printf("reserved 	%u\n", s(sections_64->reserved3, vm.is_swap));
		}
		else
		{
			printf("sectname 	%s\n", sections_32->sectname);
			printf("segname 	%s\n", sections_32->segname);
			printf("addr 	%u\n", s(sections_32->addr, vm.is_swap));
			printf("size 	%u\n", s(sections_32->size, vm.is_swap));
			printf("offset 	%u\n", s(sections_32->offset, vm.is_swap));
			printf("align 	%u\n", s(sections_32->align, vm.is_swap));
			printf("reloff 	%u\n", s(sections_32->reloff, vm.is_swap));
			printf("nreloc 	%u\n", s(sections_32->nreloc, vm.is_swap));
			printf("flags 	%u\n", s(sections_32->flags, vm.is_swap));
			printf("reserved 	%u\n", s(sections_32->reserved1, vm.is_swap));
			printf("reserved 	%u\n", s(sections_32->reserved2, vm.is_swap));
		}*/

		sec_name = vm.is_64 ? sections_64[i].sectname : sections_32[i].sectname;
		offset = vm.is_64 ? sl(sections_64[i].offset, vm.is_swap) : s(sections_32[i].offset, vm.is_swap);
		sec_size = vm.is_64 ? sl(sections_64[i].size, vm.is_swap) : s(sections_32[i].size, vm.is_swap);
		if (strncmp(sec_name, SECT_TEXT, sizeof(SECT_TEXT)) == 0)
		{
			printf("Contents of (__TEXT,__text) section\n");
			CHECK_LEN(offset + vmaddr + sec_size);
			(void)vmaddr;
			putdata(vm, vm.mem.data + offset + vmaddr, sec_size, vmaddr + offset);
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
				/*printf("\
uint32_t	cmd			%u\n\
uint32_t	cmdsize		%u\n\
char		segname		%s\n\
uint64_t	vmaddr		%llu\n\
uint64_t	vmsize		%llu\n\
uint64_t	fileoff		%llu\n\
uint64_t	filesize	%llu\n\
vm_prot_t	maxprot		%X\n\
vm_prot_t	initprot	%X\n\
uint32_t	nsects		%u\n\
uint32_t	flags		%u\n",
						c->seg64.cmd,
						c->seg64.cmdsize,
						c->seg64.segname,
						c->seg64.vmaddr,
						c->seg64.vmsize,
						c->seg64.fileoff,
						c->seg64.filesize,
						c->seg64.maxprot,
						c->seg64.initprot,
						c->seg64.nsects,
						c->seg64.flags);*/

				r = disp_sections(vm, offset, c->seg64.nsects, c->seg64.vmaddr);
			}
			else
			{
				swap_segment_32(&c->seg32, vm.is_swap);
				/*printf("\
uint32_t	cmd			%u\n\
uint32_t	cmdsize		%u\n\
char		segname		%s\n\
uint32_t	vmaddr		%u\n\
uint32_t	vmsize		%u\n\
uint32_t	fileoff		%u\n\
uint32_t	filesize	%u\n\
vm_prot_t	maxprot		%X\n\
vm_prot_t	initprot	%X\n\
uint32_t	nsects		%u\n\
uint32_t	flags		%u\n",
						c->seg32.cmd,
						c->seg32.cmdsize,
						c->seg32.segname,
						c->seg32.vmaddr,
						c->seg32.vmsize,
						c->seg32.fileoff,
						c->seg32.filesize,
						c->seg32.maxprot,
						c->seg32.initprot,
						c->seg32.nsects,
						c->seg32.flags);*/
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

t_mem				get_arch_map(t_vm vm, void *ptr, cpu_type_t *cpu)
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
		*cpu = fat_64->cputype;
	}
	else
	{
		fat_32 = (t_fat_arch*)ptr;
		out.addr = vm.is_swap ? swap(fat_32->offset) : fat_32->offset;
		out.size = vm.is_swap ? swap(fat_32->size) : fat_32->size;
		*cpu = fat_32->cputype;
	}
	out.size += out.addr;
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
		CHECK_LEN(archmem.size);
		archvm.ncmds = 0;
		r = get_vm(&archvm, archmem);
		vm.cpu = get_cpu(fuck, vm.is_swap);
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

int				disp_file(t_mem mem, char *file)
{
	int				r;
	t_vm			vm;

	r = 0;
	r = get_vm(&vm, mem);
	if (r)
		return (r);
	if (vm.is_fat)
		r = disp_archs(vm, file);
	else
		r = disp_segments(vm, file);
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
			printf("fuck %s: %i\n", argv[i], r);
		munmap(mem.data, mem.size);
	}
	ft_flush_buf();
	return (errno);
}
