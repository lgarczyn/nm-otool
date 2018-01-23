/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 21:12:06 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/23 21:49:29 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>

const char		*ft_strerror(int err)
{
	if (err < 0 || err >= sys_nerr || sys_errlist[err] == NULL)
	{
		return ("unknown error");
	}
	else
	{
		return (sys_errlist[err]);
	}
}
