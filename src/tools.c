/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:29:50 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/29 00:07:57 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

t_mem				map(char *filename)
{
	int				fd;
	struct stat		st;
	t_mem			out;

	out.data = NULL;
	if (stat(filename, &st) != 0)
		return (out);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (out);
	if (st.st_size == 0)
		return (out);
	out.data = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	out.file = out.data;
	out.size = st.st_size;
	out.offset = 0;
	close(fd);
	return (out);
}

t_ftype				get_type(void *p, bool *is_swap, bool *is_64)
{
	u32				m;

	m = *(u32*)p;
	*is_swap = (m == FAT_CIGAM || m == FAT_CIGAM_64 ||
		m == MH_CIGAM || m == MH_CIGAM_64);
	m = s(m, *is_swap);
	*is_64 = (m == FAT_MAGIC_64 || m == MH_MAGIC_64);
	if (m == FAT_MAGIC || m == FAT_MAGIC_64)
		return (f_fat);
	if (m == MH_MAGIC || m == MH_MAGIC_64)
		return (f_object);
	if (ft_strncmp("!<arch>\n", (char*)p, 8) == 0)
		return (f_ranlib);
	return (f_err);
}

const char			*get_cpu(cpu_type_t cpu, bool is_swap)
{
	static char		*names[] = {
		"", "vax", "romp", "", "ns32032", "ns32332", "", "i386",
		"mips", "ns32532", "", "hppa", "arm", "mc88000", "sparc",
		"i860", "i860_little", "rs6000", "ppc"
	};

	cpu = s(cpu, is_swap);
	if (cpu == CPU_TYPE_ANY)
		return ("any");
	if (cpu == CPU_TYPE_X86_64)
		return ("x86_64");
	if (cpu == CPU_TYPE_POWERPC64)
		return ("ppc64");
	if (cpu == CPU_TYPE_ARM64)
		return ("arm64");
	if (cpu >= CPU_TYPE_VAX && cpu <= CPU_TYPE_POWERPC)
		return (names[cpu]);
	return ("unknown");
}

int					isvalid(int c)
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
		return (3);
	if (vm.type == f_object)
		vm.cpu = get_cpu(mach_header->cputype, vm.is_swap);
	else
		vm.cpu = NULL;
	vm.ncmds = s(vm.ncmds, vm.is_swap);
	vm.target = target;
	*out = vm;
	return (0);
}

void				putdata(t_vm *vm, u8 *data, size_t size, size_t addr)
{
	size_t			i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0 && vm->is_64)
			print("%016lx\t", addr + i);
		else if (i % 16 == 0)
			print("%08lx\t", addr + i);
		if (vm->is_swap && i % 4 != 3)
			print("%02x", data[i]);
		else
			print("%02x ", data[i]);
		if (i % 16 == 15)
			print("\n");
		i++;
	}
	if (i % 16 != 0)
		print("\n");
}
