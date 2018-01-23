/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 22:29:33 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 22:29:37 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

void		ft_putstr(char const *s)
{
	size_t	ret;

	ret = write(1, s, ft_strlen(s));
	if (ret == (size_t)-1)
		ft_perror(NULL);
}
