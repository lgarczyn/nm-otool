/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:32 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 22:25:12 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int				otool(char *filename)
{
	char		*data;
	u64			len;

	data = (char*)map(filename, &len);
	if (data == NULL)
		return (1);
	

	munmap(data, len);
	return (0);
}

int				main(int argc, char **argv)
{
	int			i;

	if (argc == 1)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": at least one file must be specified", 2);
		return -1;
	}
	ft_buf(malloc(4096), 4096, 1);
	i = 0;
	while (++i < argc)
	{
		if (otool("a.out"))
			ft_perror_file_buf(argv[0], argv[i]);
	}
	return (errno);
}
