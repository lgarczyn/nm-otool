/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:29:50 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/16 02:07:15 by lgarczyn         ###   ########.fr       */
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
	out.addr = 0;
	out.size = st.st_size;
	close(fd);
	return (out);
}

int					get_type(u32 m, bool *is_swap, bool *is_64, bool *is_fat)
{
	*is_swap = (m == FAT_CIGAM || m == FAT_CIGAM_64 ||
		m == MH_CIGAM || m == MH_CIGAM_64);
	if (*is_swap)
		m = swap(m);
	*is_64 = (m == FAT_MAGIC_64 || m == MH_MAGIC_64);
	*is_fat = (m == FAT_MAGIC || m == FAT_MAGIC_64);
	if (m == MH_MAGIC || m == MH_MAGIC_64 || *is_fat)
		return (0);
	return (1);
}

const char			*get_cpu(cpu_type_t cpu, bool is_swap)
{
	static char		*names[] = {
		"", "vax", "romp", "", "ns32032", "ns32332", "", "i386",
		"mips", "ns32532", "", "hppa", "arm", "mc88000", "sparc",
		"i860", "i860_little", "rs6000", "ppc"
	};

	if (is_swap)
		cpu = swap(cpu);
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

int					get_vm(t_vm *out, t_mem mem)
{
	t_mach_header	*mach_header;
	t_fat_header	*fat_header;
	t_vm			vm;

	vm.mem = mem;
	CHECK_LEN(sizeof(t_mach_header) + mem.addr);
	mach_header = (t_mach_header*)(mem.data + mem.addr);
	fat_header = (t_fat_header*)mach_header;
	if (get_type(mach_header->magic, &vm.is_swap, &vm.is_64, &vm.is_fat))
		return (3);
	if (vm.is_fat)
	{
		vm.ncmds = fat_header->nfat_arch;
		vm.cpu = NULL;
	}
	else
	{
		vm.cpu = get_cpu(mach_header->cputype, vm.is_swap);
		vm.ncmds = mach_header->ncmds;
	}
	if (vm.is_swap)
		vm.ncmds = swap(vm.ncmds);
	*out = vm;
	//printf("GOT VM cpu:%x swap:%i 64:%i fat:%i\n", s(mach_header->cputype, vm.is_swap), vm.is_swap, vm.is_64, vm.is_fat);
	return (0);
}

void				putdata(t_vm vm, u8 *data, size_t size, size_t addr)
{
	size_t			i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0 && vm.is_64)
			printf("%016lx\t", addr + i);
		else if (i % 16 == 0)
			printf("%08lx\t", addr + i);
		if (vm.is_swap && i % 4 != 3)
			printf("%02x", data[i]);
		else
			printf("%02x ", data[i]);
		if (i % 16 == 15)
			printf("\n");
		i++;
	}
	if (i % 16 != 0)
		printf("\n");
}
