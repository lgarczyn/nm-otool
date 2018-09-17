/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:14:29 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 17:25:19 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_load_cmd			read_load(void *ptr, bool swap)
{
	t_load_cmd		*cmd;
	t_load_cmd		out;

	cmd = (t_load_cmd*)ptr;
	out.cmd = s(cmd->cmd, swap);
	out.cmdsize = s(cmd->cmdsize, swap);
	return (out);
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

t_nlist_64			read_sym_token(t_vm vm, void *p)
{
	t_nlist_64		out;
	t_nlist_64		*sym_64;
	t_nlist			*sym_32;

	sym_64 = (t_nlist_64*)p;
	sym_32 = (t_nlist*)p;
	out.n_un.n_strx = s(sym_64->n_un.n_strx, vm.is_swap);
	out.n_type = sym_64->n_type;
	out.n_sect = sym_64->n_sect;
	out.n_desc = sym_64->n_desc;
	out.n_value = vm.is_64 ?
		sl(sym_64->n_value, vm.is_swap) : s(sym_32->n_value, vm.is_swap);
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
