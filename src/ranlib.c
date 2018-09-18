/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:44:27 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 09:36:31 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

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
	out->full_len = ft_pure_atoi(head->size) + sizeof(t_ar_header);
	return (OK);
}

static int			disp_child(t_vm vm, u64 offset, char *ar, char *file)
{
	CHECK(disp_file(
		get_sub_mem(vm.mem, offset, vm.mem.size),
		vm.target, ar, file));
	return (OK);
}

int					disp_ranlib(t_vm vm, char *file)
{
	u64				offset;
	t_array			array;
	t_ar_info		info;

	ft_bzero(&array, sizeof(array));
	offset = 8 + vm.ar_info.header_len;
	if (vm.target.is_otool == true)
		print("Archive : %s\n", file);
	if (ft_strncmp(vm.ar_info.name, "__.SYMDEF", 9) == 0)
	{
		offset += GET_CHECKED_VAL(offset, u32) + sizeof(u32);
		offset += GET_CHECKED_VAL(offset, u32) + sizeof(u32);
		while (offset < vm.mem.size)
		{
			CHECK(check_ranlib_header(vm, offset, &info));
			CHECK(disp_child(vm, offset + info.header_len, info.name, file));
			offset += info.full_len;
		}
	}
	else
		CHECK(disp_child(vm, offset, vm.ar_info.name, file));
	return (OK);
}
