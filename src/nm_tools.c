/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:52:41 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 17:38:26 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static t_nlist_64	list64(t_nlist list)
{
	t_nlist_64		out;

	out.n_un.n_strx = list.n_un.n_strx;
	out.n_type = list.n_type;
	out.n_sect = list.n_sect;
	out.n_desc = list.n_desc;
	out.n_value = list.n_value;

	return (out);
}

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
			if (c > 0 || (c == 0 && tokens[i].sym > tokens[j].sym))
			{
				tmp = tokens[i];
				tokens[i] = tokens[j];
				tokens[j] = tmp;
			}
		}
	}
}

//REMEMBER TO USE IS_SWAP AND CHECK STRINGS


/*void				disp_symbol(t_vm vm, t_sym_token token, t_sect_types *types)
{
	t_nlist_64		s;

	s = vm.is_64 ? *token.sym : list64(*(t_nlist*)token.sym);
	s.n_type = get_sym_type(s, types);
	if (s.n_type == 'z' || s.n_type == 'Z' || s.n_type == '?')
		return ;
	if (vm.is_64 == false)
		if (s.n_value && s.n_type != 'U' && s.n_type != 'u')
			print("%.8llx %c %s\n", s.n_value, s.n_type, token.name);
		else
			print("% 9 %c %s\n", s.n_type, token.name);
	else if (s.n_value && s.n_type != 'U' && s.n_type != 'u')
		print("%.16llx %c %s\n", s.n_value, s.n_type, token.name);
	else
		print("% 17 %c %s\n", s.n_type, token.name);
}*/

t_nlist_64			read_sym(t_vm vm, t_nlist_64 *sym)
{
	t_nlist_64		out;
	t_nlist			*sym_32;

	sym_32 = (t_nlist*)sym;
	out.n_un.n_strx = s(sym->n_un.n_strx, vm.is_swap);
	out.n_type = sym->n_type;
	out.n_sect = sym->n_sect;
	out.n_desc = sym->n_desc;
	out.n_value = vm.is_64 ?
		sl(sym->n_value, vm.is_swap) : s(sym_32->n_value, vm.is_swap);
	return (out);
}

void				disp_symtab(t_vm vm, t_array *array, t_sect_types *types)
{
	t_sym_token		*syms;
	size_t			len;
	t_nlist_64		s;

	sort_symtab(array);
	syms = (t_sym_token*)array->data;
	len = array->pos / sizeof(t_sym_token);
	while (len--)
	{
		s = vm.is_64 ? *syms->sym : list64(*(t_nlist*)syms->sym);
		s.n_type = get_sym_type(s, types);
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
		token.sym = vm.is_64 ? &array_64[i] : (t_nlist_64*)&array[i];
		if (token.sym->n_un.n_strx == 0)
			print("lol test\n");
		token.name = string_table + token.sym->n_un.n_strx;
		//if(check_string(vm, token.name))
		//	token.name = (u8*)"OUT OF BOUNDS\n";
		if (*token.name)
			CHECK(array_push(tokens, &token, sizeof(token)));
		i++;
	}
	return (0);
}
