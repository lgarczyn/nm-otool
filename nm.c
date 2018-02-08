/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/08 03:35:07 by lgarczyn         ###   ########.fr       */
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
	sections_64 = (t_section_64*)(vm.data + offset);
	sections_32 = (t_section_32*)(vm.data + offset);
	while (i < n)
	{
		sec_name = vm.is_64 ? sections_64[i].sectname : sections_32[i].sectname;
		offset = vm.is_64 ? sections_64[i].offset : sections_32[i].offset;
		sec_size = vm.is_64 ? sections_64[i].size : sections_32[i].size;
		if (strncmp(sec_name, SECT_TEXT, sizeof(SECT_TEXT)) == 0)
		{
			printf("Contents of (__TEXT,__text) section\n");
			CHECK_LEN(offset + sec_size);
			putdata(vm.data, offset, sec_size, vmaddr);
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

int					disp_segments(t_vm vm)
{
	u64				offset;
	t_cmd			*cmd;
	u32				i;
	int				r;

	offset = vm.is_64 ? sizeof(t_mach_header_64) : sizeof(t_mach_header);
	i = 0;
	while (i++ < vm.ncmds)
	{
		CHECK_LEN(offset + sizeof(t_load_command));
		cmd = (t_cmd*)(vm.data + offset);
		swap_load(&cmd->load, vm.is_swap);
		r = disp_segment(vm, cmd, offset);
		if (r)
			return (r);
		offset += cmd->load.cmdsize;
	}
	return (0);
}

void				disp_file(char *prog, char *file)
{
	int				r;
	t_vm			vm;

	vm.data = NULL;
	r = get_vm(0, &vm, file);
	if (r == 0)
		r = disp_segments(vm);

	ft_flush_buf();

	if (r == 1)
		ft_perror_file_buf(prog, file);
	else if (r > 1)
		printf("fuck %s: %i\n", file, r);

	if (vm.data != NULL)
		munmap(vm.data, vm.len);
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
	return (errno);
}
