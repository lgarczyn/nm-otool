/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:29:50 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/26 00:20:26 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void			*map(char *filename, u64 *len)
{
	int			fd;
	char		*data;
	struct stat	st;

	if (stat(filename, &st) != 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	data = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	*len = st.st_size;
	close(fd);
	return (data);
}

void			putnstr_clean(char *str, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n) {
		if (ft_isprint(str[i])) {
			ft_putchar_buf(str[i]);
		} else {
			ft_putchar_buf('.');
		}
		i++;
	}
}
