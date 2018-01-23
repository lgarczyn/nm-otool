/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 06:08:22 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/06 06:08:24 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	word_num(char const *s, char c)
{
	int		num;
	int		i;

	i = 0;
	num = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			num++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (num);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t	pos;
	size_t	len;
	char	**tab;
	int		i;

	i = 0;
	pos = 0;
	tab = NULL;
	if (!s)
		return (tab);
	tab = (char **)ft_memalloc(sizeof(char *) * (word_num(s, c) + 1));
	while (word_num(s, c) - i)
	{
		while (s[pos] == c)
			pos++;
		len = 0;
		while (s[pos + len] && s[pos + len] != c)
			len++;
		tab[i] = ft_strsub(s, pos, len);
		pos += len;
		i++;
	}
	return (tab);
}
