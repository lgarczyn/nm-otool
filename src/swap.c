/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:14:29 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/24 01:49:58 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

u32					s(u32 x, bool swap)
{
	if (swap)
	{
		return ((x >> 24) & 0xff) | \
		((x << 8) & 0xff0000) | \
		((x >> 8) & 0xff00) | \
		((x << 24) & 0xff000000);
	}
	return (x);
}

u64					sl(u64 x, bool swap)
{
	if (swap)
	{
		x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
		x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
		x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
	}
	return (x);
}

void				swap_load(t_load_command *cmd, bool swap)
{
	cmd->cmd = s(cmd->cmd, swap);
	cmd->cmdsize = s(cmd->cmdsize, swap);
}

t_seg_cmd_64		read_segment(void *p, bool swap, bool is64)
{
	t_seg_cmd_64	out;
	t_seg_cmd_64	*p64;
	t_seg_cmd_32	*p32;

	p64 = (t_seg_cmd_64*)p;
	p32 = (t_seg_cmd_32*)p;
	out.cmd = s(p64->cmd, swap);
	out.cmdsize = s(p64->cmdsize, swap);
	ft_memmove(out.segname, &p64->segname, sizeof(out.segname));
	out.vmaddr = is64 ? sl(p64->vmaddr, swap) : s(p32->vmaddr, swap);
	out.vmsize = is64 ? sl(p64->vmsize, swap) : s(p32->vmsize, swap);
	out.fileoff = is64 ? sl(p64->fileoff, swap) : s(p32->fileoff, swap);
	out.filesize = is64 ? sl(p64->filesize, swap) : s(p32->filesize, swap);
	out.nsects = s(is64 ? p64->nsects : p32->nsects, swap);
	out.flags = s(is64 ? p64->flags : p32->flags, swap);

	print("\
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
	out.cmd,
	out.cmdsize,
	out.segname,
	out.vmaddr,
	out.vmsize,
	out.fileoff,
	out.filesize,
	out.maxprot,
	out.initprot,
	out.nsects,
	out.flags);
	return (out);
}

t_section_64		read_section(void *p, bool swap, bool is64)
{
	t_section_64	out;
	t_section_64	*p64;
	t_section_32	*p32;

	p64 = (t_section_64*)p;
	p32 = (t_section_32*)p;
	
	ft_memmove(out.sectname, &p64->sectname, sizeof(out.sectname));
	ft_memmove(out.segname, &p64->segname, sizeof(out.segname));
	out.addr = is64 ? sl(p64->addr, swap) : s(p32->addr, swap);
	out.size = is64 ? sl(p64->size, swap) : s(p32->size, swap);
	out.offset = s(is64 ? p64->offset : p32->offset, swap);
	out.align = s(is64 ? p64->align : p32->align, swap);
	out.reloff = s(is64 ? p64->reloff : p32->reloff, swap);
	out.nreloc = s(is64 ? p64->nreloc : p32->nreloc, swap);
	out.flags = s(is64 ? p64->flags : p32->flags, swap);

	print("sectname 	%s\n", out.sectname);
	print("segname 	%s\n", out.segname);
	print("addr 	%llu\n", out.addr);
	print("size 	%llu\n", out.size);
	print("offset 	%u\n", out.offset);
	print("align 	%u\n", out.align);
	print("reloff 	%u\n", out.reloff);
	print("nreloc 	%u\n", out.nreloc);
	print("flags 	%u\n", out.flags);
	print("reserved 	%u\n", out.reserved1);
	print("reserved 	%u\n", out.reserved2);
	return (out);
}
