/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 00:47:49 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:41:06 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int	i;

	i = -1;
	while ((s1[++i] || s2[i]) && i < (int)n)
		if (s1[i] != s2[i])
			return (0);
	return (1);
}
