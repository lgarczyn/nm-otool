/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 23:11:58 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 00:55:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char				get_sect_type(char *name)
{
	if (!ft_strcmp(name, SECT_DATA))
		return ('D');
	else if (!ft_strcmp(name, SECT_BSS))
		return ('B');
	else if (!ft_strcmp(name, SECT_TEXT))
		return ('T');
	else
		return ('S');
}

char				get_sym_type(t_nlist_64 sym, t_sect_types *types)
{
	char			ret;

	ret = '?';
	if ((sym.n_type & N_TYPE) == N_UNDF)
	{
		if (sym.n_value)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((sym.n_type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((sym.n_type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((sym.n_type & N_TYPE) == N_SECT)
		ret = types->data[sym.n_sect - 1];
	else if ((sym.n_type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((sym.n_type & N_STAB) != 0)
		ret = 'Z';
	if ((sym.n_type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

t_ftype				get_type(void *p, bool *is_swap, bool *is_64)
{
	u32				m;
	char			*f;

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
	f = ft_strndup((char*)p, 8);
	print("UNKOWN_TYPE: %D\n", f);
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
