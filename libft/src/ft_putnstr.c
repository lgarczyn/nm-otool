/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 18:23:51 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/27 18:23:52 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

void		ft_putnstr(char const *s, int n)
{
	size_t	ret;

	ret = write(1, s, n);
	if (ret == (size_t)-1)
		ft_perror(NULL);
}
