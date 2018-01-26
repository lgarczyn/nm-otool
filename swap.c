/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:14:29 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/26 02:40:43 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

#        include <stdio.h>

u32				swap(u32 x)
{
	return
		((x >> 24) & 0xff) |
		((x << 8) & 0xff0000) |
		((x >> 8) & 0xff00) |
		((x << 24) & 0xff000000);
}

u64				swap_64(u64 x)
{
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
	return x;
}

void			swap_header(t_mach_header *header, bool is_swap)
{
	if (is_swap)
	{
		printf("WTF BIG ENDIAN\n");
		header->magic = swap(header->magic);
		header->filetype = swap(header->filetype);
		header->ncmds = swap(header->ncmds);
		header->sizeofcmds = swap(header->sizeofcmds);
		header->flags = swap(header->flags);
	}
}

void			swap_load(t_load_command *cmd, bool is_swap)
{
	if (is_swap)
	{
		cmd->cmd = swap(cmd->cmd);
		cmd->cmdsize = swap(cmd->cmdsize);
	}
}

void			swap_segment_64(t_segment_command_64 *seg, bool is_swap)
{
	if (is_swap)
	{
		seg->vmaddr = swap_64(seg->vmaddr);
		seg->vmsize = swap_64(seg->vmsize);
		seg->fileoff = swap_64(seg->fileoff);
		seg->filesize = swap_64(seg->filesize);
		seg->nsects = swap(seg->nsects);
		seg->flags = swap(seg->flags);
	}
}

void			swap_segment_32(t_segment_command_32 *seg, bool is_swap)
{
	if (is_swap)
	{
		seg->vmaddr = swap(seg->vmaddr);
		seg->vmsize = swap(seg->vmsize);
		seg->fileoff = swap(seg->fileoff);
		seg->filesize = swap(seg->filesize);
		seg->nsects = swap(seg->nsects);
		seg->flags = swap(seg->flags);
	}
}

void			swap_section_64(t_section_64 *sect, bool is_swap)
{
	if (is_swap)
	{
		sect->addr = swap_64(sect->addr);
		sect->size = swap_64(sect->size);
		sect->offset = swap(sect->offset);
		sect->align = swap(sect->align);
		sect->reloff = swap(sect->reloff);
		sect->nreloc = swap(sect->nreloc);
		sect->flags = swap(sect->flags);
	}
}

void			swap_section_32(t_section_32 *sect, bool is_swap)
{
	if (is_swap)
	{
		sect->addr = swap(sect->addr);
		sect->size = swap(sect->size);
		sect->offset = swap(sect->offset);
		sect->align = swap(sect->align);
		sect->reloff = swap(sect->reloff);
		sect->nreloc = swap(sect->nreloc);
		sect->flags = swap(sect->flags);
	}
}
