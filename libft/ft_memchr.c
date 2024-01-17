/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:34:46 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/10 10:55:39 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *data, int c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (*(char *)(data + i) == (char)c)
			return ((void *)(data + i));
		i++;
	}
	return (NULL);
}
