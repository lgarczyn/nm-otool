/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:44:27 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 18:12:34 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		disp_filename(t_vm vm, char *file, char *ar)
{
	if (vm.target.show_cpu)
		print("\n%s (%sarchitecture %s):\n",
			file, vm.target.is_otool ? "" : "for ", get_cpu(vm.cpu));
	else if (ar)
		print("%s%s(%s):\n", vm.target.is_otool ? "" : "\n", ar, file);
	else if (vm.target.show_names)
		print("%s%s:\n", vm.target.is_otool ? "" : "\n", file);
}

void		disp_data(t_vm *vm, u8 *data, size_t size, size_t addr)
{
	size_t	i;

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
