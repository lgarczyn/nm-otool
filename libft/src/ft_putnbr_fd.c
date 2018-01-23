/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 22:27:58 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/05 22:28:04 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

void			ft_putnbr_fd(int n, int fd)
{
	static char	buffer[11];
	size_t		ret;
	int			i;
	int			isneg;
	int			len;

	if (fd < 0)
		return ;
	len = ft_intlen(n);
	i = len - 1;
	isneg = n < 0;
	if (isneg)
	{
		buffer[0] = '-';
		buffer[i--] = '0' - (n % 10);
		n = -(n / 10);
	}
	while (i >= isneg)
	{
		buffer[i--] = '0' + (n % 10);
		n /= 10;
	}
	ret = write(fd, buffer, len);
	if (ret == (size_t)-1)
		ft_perror(NULL);
}
