/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 18:12:51 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static int			nm_filter(char *p, char *f, int r)
{
	if (r == 1)
		return (1);
	if (r == ERR_MAGIC)
	{
		printerr(
			"%s: %s The file was not recognized as a valid object file\n\n",
			p, f);
		return (1);
	}
	return (gen_filter(r, p, f));
}

int					main(int argc, char **argv)
{
	int				i;
	t_mem			mem;
	t_target		target;

	target.is_otool = false;
	ft_buf(malloc(4096), 4096, 1);
	if (argc == 1)
	{
		argc = 2;
		argv[1] = "a.out";
	}
	target.show_names = argc > 2;
	i = 0;
	while (++i < argc)
	{
		if (nm_filter(argv[0], argv[i], map(&mem, argv[i])))
			continue;
		nm_filter(argv[0], argv[i], disp_file(mem, target, argv[i], NULL));
		nm_filter(argv[0], argv[i], munmap(mem.data, mem.size));
	}
	ft_flush_buf();
	return (errno);
}
