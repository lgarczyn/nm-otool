/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:14:29 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/29 01:43:53 by lgarczyn         ###   ########.fr       */
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

void				swap_load(t_load_cmd *cmd, bool swap)
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
	ft_memmove(out.segname, &p64->segname, sizeof(out.segname));
	out.vmaddr = is64 ? sl(p64->vmaddr, swap) : s(p32->vmaddr, swap);
	out.vmsize = is64 ? sl(p64->vmsize, swap) : s(p32->vmsize, swap);
	out.fileoff = is64 ? sl(p64->fileoff, swap) : s(p32->fileoff, swap);
	out.filesize = is64 ? sl(p64->filesize, swap) : s(p32->filesize, swap);
	out.nsects = s(is64 ? p64->nsects : p32->nsects, swap);
	out.flags = s(is64 ? p64->flags : p32->flags, swap);
	return (out);
}

t_symtab_cmd		read_symtab_cmd(void *p, bool is_swap)
{
	t_symtab_cmd	out;
	t_symtab_cmd	*in;

    in = (t_symtab_cmd*)p;

	out.symoff = s(in->symoff, is_swap);
	out.nsyms = s(in->nsyms, is_swap);
	out.stroff = s(in->stroff, is_swap);
	out.strsize = s(in->strsize, is_swap);

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
	return (out);
}
