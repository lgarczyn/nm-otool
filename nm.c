/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/26 02:41:57 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

#   include <stdio.h>

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
uint32_t	flags		%u\n\
u64			len			%llu\n\
bool		is_swap		%i\n\
bool		is_64		%i\n\
u32			type		%u\n\
offset					%llu\n\
sizeof					%lu\n\
sec						%llu\n", 

						cmd->segment_64.cmd,
						cmd->segment_64.cmdsize,
						cmd->segment_64.segname,
						cmd->segment_64.vmaddr,
						cmd->segment_64.vmsize,
						cmd->segment_64.fileoff,
						cmd->segment_64.filesize,
						cmd->segment_64.maxprot,
						cmd->segment_64.initprot,
						cmd->segment_64.nsects,
						cmd->segment_64.flags,
						file.len,
						file.is_swap,
						file.is_64,
						file.type,
						offset,
						sizeof(cmd->segment_64),
						offset + sizeof(cmd->segment_64));*/
/*printf("\
char		sectname	%s\n\
char		segname		%s\n\
uint64_t	addr		%llu\n\
uint64_t	size		%llu\n\
uint32_t	offset		%u\n\
uint32_t	align		%u\n\
uint32_t	reloff		%u\n\
uint32_t	nreloc		%u\n\
uint32_t	flags		%u\n", 

						sections[i].sectname,
						sections[i].segname,
						sections[i].addr,
						sections[i].size,
						sections[i].offset,
						sections[i].align,
						sections[i].reloff,
						sections[i].nreloc,
						sections[i].flags);*/

#define CHECK_LEN(l) do{if (l > env.len) return (100 + __COUNTER__);}while(0)

int					display_sections_64(t_env env, u64 offset, u64 num)
{
	t_section_64	*sections;
	u64				i;

	CHECK_LEN(offset + num * sizeof(t_section_64));
	sections = (t_section_64*)(env.data + offset);
	i = 0;
	while (i < num)
	{
		if (strncmp(sections[i].sectname, SECT_TEXT, sizeof(SECT_TEXT)) == 0)
		{
			CHECK_LEN(sections[i].offset + sections[i].size);
			putnstr_clean(env.data + sections[i].offset, sections[i].size);
		}
		i++;
	}
	return (0);
}

int					display_sections_32(t_env env, u64 offset, u32 num)
{
	t_section_32	*sections;
	u32				i;

	CHECK_LEN(offset + num * sizeof(t_section_32));
	sections = (t_section_32*)(env.data + offset);
	i = 0;
	while (i < num)
	{
		if (strncmp(sections[i].sectname, SECT_TEXT, sizeof(SECT_TEXT)) == 0)
		{
			CHECK_LEN(sections[i].offset + sections[i].size);
			ft_putnstr_buf(env.data + sections[i].offset, sections[i].size);
		}
		i++;
	}
	return (0);
}

int					display_segment(t_env env, t_cmd *cmd, u64 offset)
{
	int				r;

	if (cmd->load.cmd == LC_SEGMENT_64 || cmd->load.cmd == LC_SEGMENT) {
		CHECK_LEN(offset + sizeof(cmd->name));
		ft_putnendl_buf(cmd->name.segname, 16);
		if (ft_strncmp(cmd->name.segname, SEG_TEXT, sizeof(SEG_TEXT)) == 0) {
			if (env.is_64) {
				offset = offset + sizeof(cmd->segment_64);
				CHECK_LEN(offset);
				swap_segment_64(&cmd->segment_64, env.is_swap);
				r = display_sections_64(env, offset, cmd->segment_64.nsects);
			} else {
				offset = offset + sizeof(cmd->segment_32);
				CHECK_LEN(offset);
				swap_segment_32(&cmd->segment_32, env.is_swap);
				r = display_sections_32(env, offset, cmd->segment_64.nsects);
			}
			if (r)
				return r;
		}
	}
	return (0);
}

int					display_segments(t_env env)
{
	u64				offset;
	t_cmd			*cmd;
	u32				i;
	int				r;
	
	offset = env.is_64 ? sizeof(t_mach_header_64) : sizeof(t_mach_header);
	i = 0;
	while (i++ < env.ncmds)
	{
		CHECK_LEN(offset + sizeof(t_load_command));
		cmd = (t_cmd*)(env.data + offset);
		swap_load(&cmd->load, env.is_swap);
		r = display_segment(env, cmd, offset);
		if (r)
			return (r);
		offset += cmd->load.cmdsize;
	}
	return (0);
}

int					get_env(t_env *f, char *filename)
{
	t_env			env;
	t_mach_header	*header;

	env.data = (char*)map(filename, &env.len);
	if (env.data == NULL)
		return (1);
	CHECK_LEN(sizeof(t_mach_header));
	header = (t_mach_header*)env.data;
	env.is_swap = (header->magic == MH_CIGAM || header->magic == MH_CIGAM_64);
	swap_header(header, env.is_swap);
	printf("%x\n", header->magic);
	if (header->magic != MH_MAGIC && header->magic != MH_MAGIC_64)
		return (3);
	env.is_64 = header->magic == MH_MAGIC_64;
	if (header->filetype > MH_KEXT_BUNDLE)
		return (4);
	env.type = header->filetype;
	env.ncmds = header->ncmds;
	CHECK_LEN(sizeof(t_mach_header) + header->sizeofcmds);

	*f = env;
	return (0);
}

void				display_file(char *prog, char *file)
{
	int				r;
	t_env			env;

	env.data = NULL;
	r = get_env(&env, file);
	if (r == 0)
		r = display_segments(env);

	ft_flush_buf();

	if (r == 1)
		ft_perror_file_buf(prog, file);
	else if (r > 1)
		printf("fuck %s: %i\n", file, r);

	if (env.data != NULL)
		munmap(env.data, env.len);
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
		display_file(argv[0], argv[1]);
	}
	return (errno);
}
