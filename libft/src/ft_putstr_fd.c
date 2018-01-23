/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 22:29:05 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 22:29:10 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

void		ft_putstr_fd(char const *s, int fd)
{
	size_t	ret;

	ret = write(fd, s, ft_strlen(s));
	if (ret == (size_t)-1)
		ft_perror(NULL);
}
