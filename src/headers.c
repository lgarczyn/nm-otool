/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:29:50 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 19:13:45 by lgarczyn         ###   ########.fr       */
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
		return (ERR_MAGIC);
	out->data = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (out->data == NULL || out->data == (u8*)-1)
		return (errno);
	out->file = out->data;
	out->size = st.st_size;
	out->offset = 0;
	close(fd);
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
		return (ERR_MAGIC);
	vm.cpu = vm.type == f_object ? s(mach_header->cputype, vm.is_swap) : 0;
	vm.ncmds = s(vm.ncmds, vm.is_swap);
	vm.target = target;
	*out = vm;
	return (0);
}

t_mem				get_arch_map(t_vm vm, void *ptr, cpu_type_t *cpu)
{
	u64				addr;
	u64				size;
	t_fat_arch		*fat_32;
	t_fat_arch_64	*fat_64;

	fat_32 = (t_fat_arch*)ptr;
	fat_64 = (t_fat_arch_64*)ptr;
	*cpu = s(fat_32->cputype, vm.is_swap);
	if (vm.is_64)
	{
		addr = sl(fat_64->offset, vm.is_swap);
		size = sl(fat_64->size, vm.is_swap);
	}
	else
	{
		addr = s(fat_32->offset, vm.is_swap);
		size = s(fat_32->size, vm.is_swap);
	}
	return (get_sub_mem(vm.mem, addr, size));
}
