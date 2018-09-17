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

static int			nm_filter(int r, char *p, char *f)
{
	if (r == ERR_MAGIC)
	{
		printerr(
			"%s: %s The file was not recognized as a valid object file\n",
			p, f);
		return (0);
	}
	return (r);
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
	target.disp_names = argc > 2;
	i = 0;
	while (++i < argc)
	{
		CHECK_SKIP(argv[0], argv[i], map(&mem, argv[i]));
		CHECK_DISP(argv[0], argv[i], nm_filter(
			disp_file(mem, target, argv[i], NULL),
			argv[0], argv[i]));
		CHECK_DISP(argv[0], argv[i], munmap(mem.data, mem.size));
	}
	ft_flush_buf();
	return (errno);
}
