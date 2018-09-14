/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:52:41 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 09:04:59 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static t_nlist_64	list_tolist64(t_nlist list)
{
	t_nlist_64		out;

	out.n_un.n_strx = list.n_un.n_strx;
	out.n_type = list.n_type;
	out.n_sect = list.n_sect;
	out.n_desc = list.n_desc;
	out.n_value = list.n_value;

	return out;
}

static void			swap_symtab(t_sym_token *a, t_sym_token  *b)
{
	t_sym_token		tmp;

	tmp.sym = a->sym;
	tmp.name = a->name;
	a->sym = b->sym;
	a->name = b->name;
	b->sym = tmp.sym;
	b->name = tmp.name;
}

static void			sort_symtab(t_array *array)
{
	t_sym_token		*tokens;
	size_t			len;
	size_t			i;
	size_t			j;
	int				c;

	tokens = (t_sym_token*)array->data;
	len = array->pos / sizeof(t_sym_token);
	i = 0;
	while (i < len)
	{
		j = i;
		while (++j < len)
		{
			c = ft_strcmp((char*)tokens[i].name, (char*)tokens[j].name);
			if (c > 0 || (c == 0 && tokens[i].sym > tokens[j].sym))
				swap_symtab(tokens + i, tokens + j);
			/*else if (c == 0)
			{
				tokens[i].sym = NULL;
				tokens[i].name = NULL;
			}*/
		}
		i++;
	}
}

//REMEMBER TO USE IS_SWAP

void				disp_symtab(t_vm vm, t_array *array, t_sect_types *types)
{
	t_sym_token		*tokens;
	size_t			len;
	size_t			i;
	t_nlist_64		s;

	sort_symtab(array);
	tokens = (t_sym_token*)array->data;
	len = array->pos / sizeof(t_sym_token);
	i = -1;
	while (++i < len)
		if (tokens[i].sym)
		{
			s = vm.is_64 ? *tokens[i].sym : list_tolist64(*(t_nlist*)tokens[i].sym);
			s.n_type = get_sym_type(s, types);
			if (s.n_type == 'z' || s.n_type == 'Z' || s.n_type == '?')
				continue;
			if (vm.cpu != CPU_TYPE_I386)
				if (s.n_value || s.n_type == 'T')
					print("%.16llx %c %s\n", s.n_value, s.n_type, tokens[i].name);
				else
					print("% 17 %c %s\n", s.n_type, tokens[i].name);
			else if (s.n_value || s.n_type == 'T')
				print("%.8llx %c %s\n", s.n_value, s.n_type, tokens[i].name);
			else
				print("% 9 %c %s\n", s.n_type, tokens[i].name);
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
	CHECK_LEN(cmd.symoff + cmd.nsyms * (vm.is_64 ? sizeof(t_nlist_64) : sizeof(t_nlist)));
	i = 0;
	while (i < cmd.nsyms)
	{
		token.sym = vm.is_64 ? &array_64[i] : (t_nlist_64*)&array[i];
		if (token.sym->n_un.n_strx == 0)
			print("lol test\n");
		token.name = string_table + token.sym->n_un.n_strx;
		CHECK(check_string(vm, token.name));
		CHECK(array_push(tokens, &token, sizeof(token)));
		i++;
	}
	return (0);
}