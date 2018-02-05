/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:29:50 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/26 17:05:11 by lgarczyn         ###   ########.fr       */
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

int					get_vm(t_vm *out, char *filename)
{
	t_mach_header	*header;
	t_vm			vm;

	vm.data = (char*)map(filename, &vm.len);
	if (vm.data == NULL)
		return (1);
	if (sizeof(t_mach_header) > vm.len)
		return 2;
	header = (t_mach_header*)vm.data;
	vm.is_swap = (header->magic == MH_CIGAM || header->magic == MH_CIGAM_64);
	swap_header(header, vm.is_swap);
	//printf("%x\n", header->magic);
	if (header->magic != MH_MAGIC && header->magic != MH_MAGIC_64)
		return (3);
	vm.is_64 = header->magic == MH_MAGIC_64;
	if (header->filetype > MH_KEXT_BUNDLE)
		return (4);
	vm.type = header->filetype;
	vm.ncmds = header->ncmds;
	CHECK_LEN(sizeof(t_mach_header) + header->sizeofcmds);
	*out = vm;
	return (0);
}

//TODO optimize
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
