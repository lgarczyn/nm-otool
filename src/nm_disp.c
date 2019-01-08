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

static int			should_swap(t_sym_token a, t_sym_token b, t_target t)
{
	int				c;

	if (t.sorting == no_sorting)
		return (0);
	if (t.sorting == sort_alphabetical)
		c = ft_strcmp((char*)a.name, (char*)b.name);
	else
		c = 0;
	if (c == 0)
		c = a.sym.n_value > b.sym.n_value;
	if (c < 0)
		c = 0;
	if (t.reversed)
		return (!c);
	return (c);
}

static void			sort_symtab(t_array *array, t_target target)
{
	t_sym_token		*tokens;
	size_t			i;
	size_t			j;
	t_sym_token		tmp;

	tokens = (t_sym_token*)array->data;
	i = -1;
	while (++i < array->pos / sizeof(t_sym_token))
	{
		j = i;
		while (++j < array->pos / sizeof(t_sym_token))
		{
			if (should_swap(tokens[i], tokens[j], target))
			{
				tmp = tokens[i];
				tokens[i] = tokens[j];
				tokens[j] = tmp;
			}
		}
	}
}

static void			disp_sym(t_vm vm, char t, t_sym_token *syms)
{
	if (t != 'z' && t != 'Z' && t != '?')
	{
		if (vm.target.only_name)
			print("%s\n", syms->name);
		else if (vm.is_64)
			if (t != 'U' && t != 'u')
				print("%.16llx %c %s\n", syms->sym.n_value, t, syms->name);
			else
				print("% 17 %c %s\n", t, syms->name);
		else if (t != 'U' && t != 'u')
			print("%.8llx %c %s\n", syms->sym.n_value, t, syms->name);
		else
			print("% 9 %c %s\n", t, syms->name);
	}
}

void				disp_symtab(t_vm vm, t_array *symtab, t_array *sect_types)
{
	t_sym_token		*syms;
	size_t			len;
	char			t;

	sort_symtab(symtab, vm.target);
	syms = (t_sym_token*)symtab->data;
	len = symtab->pos / sizeof(t_sym_token);
	while (len--)
	{
		t = get_sym_type(syms->sym, sect_types);
		disp_sym(vm, t, syms);
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
		CHECK(array_push(tokens, &token, sizeof(token)));
		i++;
	}
	return (OK);
}
