/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   public.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 16:31:19 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/09 04:09:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUBLIC_H
# define PUBLIC_H

int						printerr(const char *restrict format, ...);
int						printfd(int fd, const char *restrict format, ...);
int						printf(const char *restrict format, ...);
int						print(const char *restrict format, ...);

#endif
