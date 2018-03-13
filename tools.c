/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:29:50 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/03/13 02:13:17 by lgarczyn         ###   ########.fr       */
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
	out.size = st.st_size;
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

int					check_ranlib_header(t_vm vm, u64 pos, u64 *out)
{
	u64				offset;
	t_ar_header		*head;

	CHECK_LEN(pos + sizeof(t_ar_header));
	head = (t_ar_header*)(vm.mem.data + pos);
	print("name %s\n", ft_strndup(head->name, sizeof(head->name)));
	print("date %s\n", ft_strndup(head->date, sizeof(head->date)));
	print("uid %s\n", ft_strndup(head->uid, sizeof(head->uid)));
	print("gid %s\n", ft_strndup(head->gid, sizeof(head->gid)));
	print("mode %s\n", ft_strndup(head->mode, sizeof(head->mode)));
	print("size %s\n", ft_strndup(head->size, sizeof(head->size)));
	offset = 0;
	if (ft_strncmp("#1/", head->name, 3) == 0)
	{
		offset = ft_pure_atoi(head->name + 3);
		if (offset > 256)
			return (1);
		CHECK_LEN(pos + sizeof(t_ar_header) + offset);
		print("real name: %s\n", ft_strndup(head->long_name, offset));
	}
	if (ft_strncmp("  `\n", head->end, 4) != 0)
		return (1);
	*out = sizeof(t_ar_header) + offset;
	return (0);
}

int					get_vm(t_vm *out, t_mem mem)
{
	t_mach_header	*mach_header;
	t_fat_header	*fat_header;
	t_vm			vm;
	u64				offset;

	vm.mem = mem;
	CHECK_LEN(sizeof(t_mach_header));
	mach_header = (t_mach_header*)mem.data;
	fat_header = (t_fat_header*)mem.data;
	vm.type = get_type(mem.data, &vm.is_swap, &vm.is_64);
	if (vm.type == f_ranlib && check_ranlib_header(vm, 8, &offset))
		vm.ncmds = offset;
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
	*out = vm;
	print("GOT VM cpu:%x swap:%i 64:%i type:%i\n", s(mach_header->cputype, vm.is_swap), vm.is_swap, vm.is_64, vm.type);
	return (0);
}

void				putdata(t_vm vm, u8 *data, size_t size, size_t addr)
{
	size_t			i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0 && vm.is_64)
			print("%016lx\t", addr + i);
		else if (i % 16 == 0)
			print("%08lx\t", addr + i);
		if (vm.is_swap && i % 4 != 3)
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
