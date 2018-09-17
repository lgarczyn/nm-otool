/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_disp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:52:41 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 17:38:26 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static void			sort_symtab(t_array *array)
{
	t_sym_token		*tokens;
	size_t			i;
	size_t			j;
	int				c;
	t_sym_token		tmp;

	tokens = (t_sym_token*)array->data;
	i = -1;
	while (++i < array->pos / sizeof(t_sym_token))
	{
		j = i;
		while (++j < array->pos / sizeof(t_sym_token))
		{
			c = ft_strcmp((char*)tokens[i].name, (char*)tokens[j].name);
			if (c == 0)
				c = tokens[i].sym.n_value > tokens[j].sym.n_value;
			if (c > 0)
			{
				tmp = tokens[i];
				tokens[i] = tokens[j];
				tokens[j] = tmp;
			}
		}
	}
}

void				disp_symtab(t_vm vm, t_array *symtab, t_array *sect_types)
{
	t_sym_token		*syms;
	size_t			len;
	t_nlist_64		s;

	sort_symtab(symtab);
	syms = (t_sym_token*)symtab->data;
	len = symtab->pos / sizeof(t_sym_token);
	while (len--)
	{
		s = syms->sym;
		s.n_type = get_sym_type(s, sect_types);
		if (s.n_type != 'z' && s.n_type != 'Z' && s.n_type != '?')
		{
			if (vm.is_64)
				if (s.n_type != 'U' && s.n_type != 'u')
					print("%.16llx %c %s\n", s.n_value, s.n_type, syms->name);
				else
					print("% 17 %c %s\n", s.n_type, syms->name);
			else if (s.n_type != 'U' && s.n_type != 'u')
				print("%.8llx %c %s\n", s.n_value, s.n_type, syms->name);
			else
				print("% 9 %c %s\n", s.n_type, syms->name);
		}
		syms++;
	}
}

int					store_symtab(t_vm vm, t_symtab_cmd cmd, t_array *tokens)
{
	u32			i;
	t_nlist		*array;
	t_nlist_64	*array_64;
	u8			*string_table;
	t_sym_token	token;

	array = (t_nlist*)(vm.mem.data + cmd.symoff);
	array_64 = (t_nlist_64*)(vm.mem.data + cmd.symoff);
	string_table = vm.mem.data + cmd.stroff;
	CHECK_LEN(cmd.symoff + cmd.nsyms *
		(vm.is_64 ? sizeof(t_nlist_64) : sizeof(t_nlist)));
	i = 0;
	while (i < cmd.nsyms)
	{
		token.sym = read_sym_token(vm,
			vm.is_64 ? (void*)&array_64[i] : (void*)&array[i]);
		token.name = string_table + token.sym.n_un.n_strx;
		if (check_string(vm, token.name))
			token.name = (u8*)"OUT OF BOUNDS";
		if (*token.name)
			CHECK(array_push(tokens, &token, sizeof(token)));
		i++;
	}
	return (OK);
}