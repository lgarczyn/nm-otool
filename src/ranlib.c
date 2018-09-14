/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranlib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:44:27 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 09:36:31 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static int			disp_ranlib_child(t_vm vm, u64 offset, char *ar, char *file)
{
	CHECK(disp_file(
		get_sub_mem(vm.mem, offset, vm.mem.size),
		vm.target, ar, file));
	return (0);
}

int					disp_ranlib(t_vm vm, char *file)
{
	u64				offset;
	t_symdef		*sym;
	u32				i;
	t_ar_info		info;

	offset = 8 + vm.ar_info.header_len;
	print("Archive : %s\n", file);
	if (ft_strncmp(vm.ar_info.name, "__.SYMDEF", 9) == 0)
	{
		sym = (t_symdef*)GET_CHECKED_PTR(
			offset + sizeof(u32),
			vm.ar_info.ncmds * sizeof(t_symdef));
		i = 0;
		while (i < vm.ar_info.ncmds)
		{
			CHECK(check_ranlib_header(vm, sym[i].object, &info));
			CHECK(disp_ranlib_child(vm, sym[i].object + info.header_len,
				info.name, file));
			i++;
			(void)file;
		}
	}
	else
		disp_ranlib_child(vm, offset, vm.ar_info.name, file);
	return (0);
}