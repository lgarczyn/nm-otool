/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 22:26:38 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 22:26:41 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		ft_putchar_fd(char c, int fd)
{
	size_t	ret;

	ret = write(fd, &c, 1);
	if (ret == (size_t)-1)
		ft_perror(NULL);
}
