/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 18:24:05 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:46:22 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

void		ft_putnstr_fd(char const *s, int fd, int n)
{
	size_t	ret;

	ret = write(fd, s, n);
	if (ret == (size_t)-1)
		ft_perror(NULL);
}
