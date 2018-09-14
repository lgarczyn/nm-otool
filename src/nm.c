/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/14 09:34:57 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

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
		CHECK_SKIP(argv[i], map(&mem, argv[i]));
		CHECK_DISP(argv[i], disp_file(mem, target, argv[i], NULL));
		munmap(mem.data, mem.size);
	}
	ft_flush_buf();
	return (errno);
}
