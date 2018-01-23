/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 22:25:10 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 22:25:11 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		ft_putchar(char c)
{
	size_t	ret;

	ret = write(1, &c, 1);
	if (ret == (size_t)-1)
		ft_perror(NULL);
}
