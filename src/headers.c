/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:29:50 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 09:22:57 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int					map(t_mem *out, char *filename)
{
	int				fd;
	struct stat		st;

	out->data = NULL;
	if (stat(filename, &st) != 0)
		return (errno);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (errno);
	if (st.st_size == 0)
		return (EINVAL);
	out->data = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (out->data == NULL || out->data == (u8*)-1)
		return (errno);
	out->file = out->data;
	out->size = st.st_size;
	out->offset = 0;
	close(fd);
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

static int			isvalid(int c)
{
	return (c > ' ' || c <= '~');
}

int					check_ranlib_header(t_vm vm, u64 pos, t_ar_info *out)
{
	u64				offset;
	t_ar_header		*head;

	CHECK_LEN(pos + sizeof(t_ar_header) + sizeof(u32));
	head = (t_ar_header*)(vm.mem.data + pos);
	offset = 0;
	if (ft_strncmp("  `\n", head->end, 4) != 0)
		return (1);
	if (ft_strncmp("#1/", head->name, 3) == 0)
	{
		offset = ft_pure_atoi(head->name + 3);
		CHECK(offset > 256);
		CHECK_LEN(pos + sizeof(t_ar_header) + offset + sizeof(u32));
		out->name = ft_strndupwhile(head->long_name, offset, &isvalid);
	}
	else
	{
		out->name = ft_strndupwhile(head->name, 16, &isvalid);
	}
	out->header_len = offset + sizeof(t_ar_header);
	out->ncmds = GET_CHECKED_VAL(pos + offset + sizeof(t_ar_header), u32) / 8;
	return (0);
}

int					get_vm(t_vm *out, t_mem mem, t_target target)
{
	t_mach_header	*mach_header;
	t_fat_header	*fat_header;
	t_vm			vm;
	t_ar_info		ar_info;

	vm.mem = mem;
	CHECK_LEN(sizeof(t_mach_header));
	mach_header = (t_mach_header*)mem.data;
	fat_header = (t_fat_header*)mem.data;
	vm.type = get_type(mem.data, &vm.is_swap, &vm.is_64);
	if (vm.type == f_ranlib && check_ranlib_header(vm, 8, &ar_info) == 0)
		vm.ar_info = ar_info;
	else if (vm.type == f_fat)
		vm.ncmds = fat_header->nfat_arch;
	else if (vm.type == f_object)
		vm.ncmds = mach_header->ncmds;
	else
		return (EINVAL);
	vm.cpu = vm.type == f_object ? s(mach_header->cputype, vm.is_swap) : 0;
	vm.ncmds = s(vm.ncmds, vm.is_swap);
	vm.target = target;
	*out = vm;
	return (0);
}
