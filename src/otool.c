/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:32 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 18:12:54 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static int			otool_filter(char *p, char *file, int r)
{
	if (r == 1)
		return (1);
	if (r == ERR_MAGIC)
	{
		print("%s: is not an object file\n", file);
		return (1);
	}
	return (gen_filter(r, p, file));
}

static t_target		get_otool_target(void)
{
	t_target		target;

	target.show_data = false;
	target.show_text = false;
	target.show_names = true;
	target.is_otool = true;
	return (target);
}

void				filter_args(int *argc, char **argv, t_target *target)
{
	int				i;
	int				j;
	char			c;

	if (*argc == 1)
	{
		*argc = 2;
		argv[1] = "a.out";
		return ;
	}
	i = 0;
	while (++i < *argc && argv[i][0] == '-')
	{
		j = -1;
		while ((c = argv[i][++j]))
		{
			if (c == 't')
				target->show_text = true;
			if (c == 'd')
				target->show_data = true;
		}
		argv[i] = NULL;
	}
}

int					main(int argc, char **argv)
{
	int				i;
	t_mem			mem;
	t_target		target;

	target = get_otool_target();
	ft_buf(malloc(4096), 4096, 1);
	filter_args(&argc, argv, &target);
	i = 0;
	while (++i < argc)
	{
		if (argv[i] == 0)
			continue;
		if (otool_filter(argv[0], argv[i], map(&mem, argv[i])))
			return (1);
		if (otool_filter(argv[0], argv[i], disp_file(mem, target, argv[i], 0)))
			return (1);
		if (otool_filter(argv[0], argv[1], munmap(mem.data, mem.size)))
			return (1);
	}
	ft_flush_buf();
	return (OK);
}
