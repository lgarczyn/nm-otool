/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 16:19:51 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/01/25 20:46:19 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** if *ptr is null, it will always be allocated to new size
** if not, its data will be transfered, and freed
** if the data cannot fit, it is truncated
** the data is NOT automatically null terminated
** if malloc should fail, the data is unaffected, a non-zero value is returned
*/

int				ft_realloc(void **ptr, size_t old_size, size_t new_size)
{
	void		*mem;

	if (*ptr == NULL)
	{
		*ptr = ft_memalloc(new_size);
		if (!*ptr)
			return (1);
	}
	mem = ft_memalloc(new_size);
	if (mem == NULL)
		return (1);
	ft_memmove(mem, *ptr, MIN(new_size, old_size));
	free(*ptr);
	*ptr = mem;
	return (0);
}

/*
** if *ptr is null, it will always be allocated to old_size * 2
** if old_size is null or negative, it will set to 2;
** if malloc should fail, the data is unaffected, a non-zero value is returned
*/

int				ft_realloc_double(void **ptr, size_t *old_size)
{
	size_t		new_size;

	if (*old_size <= 0)
		*old_size = 0;
	new_size = *old_size == 0 ? 32 : *old_size * 2;
	if (ft_realloc(ptr, *old_size, new_size))
		return (1);
	*old_size = new_size;
	return (0);
}
int				ft_realloc_array(t_array *array)
{
	return (ft_realloc_double(&array->data, &array->size));
}
