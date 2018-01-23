/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:40:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/23 21:52:36 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libft.h>

void			*map(char *filename)
{
	int			fd;
	char		*data;
	struct stat	st;

	if (stat(filename, &st) != 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	data = mmap(0, st.st_size, PROT_READ, 0, fd, 0);
	return (data);
}

int				fn(char *filename)
{
	char		*data;

	data = (char*)map(filename);
	if (data == NULL)
		return (1);
	return (0);
}

int				main(int argc, char **argv)
{
	int			i;

	ft_buf(malloc(4096), 4096, 1);
	if (argc == 1)
	{
		if (fn("a.out"))
			ft_perror_file_buf(argv[0], "a.out");
	}
	i = 0;
	while (++i < argc)
	{
		if (fn("a.out"))
			ft_perror_file_buf(argv[0], argv[i]);
	}
	return (errno);
}
