/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:29:50 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/08 03:34:43 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void				*map(char *filename, u64 *len)
{
	int				fd;
	char			*data;
	struct stat		st;

	if (stat(filename, &st) != 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	data = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	*len = st.st_size;
	close(fd);
	return (data);
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
		"", "vax", "romp", "ns32032", "ns32332", "i386",
		"mips", "ns32532", "hppa", "arm", "mc88000", "sparc",
		"i860", "i860_little", "rs6000", "powerpc"
	};

	if (is_swap)
		cpu = swap(cpu);
	if (cpu == CPU_TYPE_ANY)
		return ("any");
	if (cpu == CPU_TYPE_X86_64)
		return ("x86_64");
	if (cpu == CPU_TYPE_POWERPC64)
		return ("powerpc64");
	if (cpu == CPU_TYPE_ARM64)
		return ("arm64");
	if (cpu >= CPU_TYPE_VAX && cpu <= CPU_TYPE_POWERPC)
		return (names[cpu]);
	return ("unknown");
}

int					get_vm(u64 offset, t_vm *vm, char *filename)
{
	t_mach_header	*mach_header;
	t_fat_header	*fat_header;

	// vm->data = (char*)map(filename, &vm->len);
	// if (vm->data == NULL)
	// 	return (1);
	// if (sizeof(t_mach_header) > vm->len)
	// 	return 2;
	mach_header = (t_mach_header*)vm->data;
	fat_header = (t_fat_header*)vm->data;
	if (get_type(mach_header->magic, &vm->is_swap, &vm->is_64, &vm->is_fat))
		return 3;
	if (vm->is_fat)
		vm->ncmds = fat_header->nfat_arch;
	else
		vm->ncmds = mach_header->ncmds;
	if (vm->is_swap)
		vm->ncmds = swap(vm->ncmds);
	if (vm->is_fat)
		return (0);
	if (offset == 0)
		printf("%s:\n", filename);
	else
		printf("%s (architecture %s):\n",
			filename, get_cpu(mach_header->cputype, vm->is_swap));
	return (0);
}

void				putdata(char *file, size_t offset, size_t size, size_t vm)
{
	size_t			i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
			printf("%016lx\t", offset + vm + i);

		printf("%02x ", file[offset + i]);

		if (i % 16 == 15)
			printf("\n");
		i++;
	}
	if (i % 16 != 0)
		printf("\n");
}
