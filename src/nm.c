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

static void			filter_args(int argc, char **argv, t_target *target)
{
	int				i;
	int				j;
	char			c;

	target->show_names = argc > 2;
	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		j = -1;
		while ((c = argv[i][++j]))
			if (c == 'a')
				target->show_all = true;
		argv[i] = NULL;
	}
}

static void			check_args(int *argc, char **argv)
{
	if (*argc == 1)
	{
		*argc = 2;
		argv[1] = "a.out";
	}
}

int					main(int argc, char **argv)
{
	int				i;
	t_mem			mem;
	t_target		target;

	ft_bzero(&target, sizeof(t_target));
	target.is_otool = false;
	check_args(&argc, argv);
	filter_args(argc, argv, &target);
	ft_buf(malloc(4096), 4096, 1);
	i = 0;
	while (++i < argc)
	{
		if (argv[i] == NULL)
			continue;
		if (nm_filter(argv[0], argv[i], map(&mem, argv[i])))
			continue;
		nm_filter(argv[0], argv[i], disp_file(mem, target, argv[i], NULL));
		nm_filter(argv[0], argv[i], munmap(mem.data, mem.size));
	}
	ft_flush_buf();
	return (errno);
}
