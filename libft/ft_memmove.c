/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:37:15 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 14:27:58 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char		*dest1;
	const char	*src1;
	size_t		i;

	if (!dest && !src)
		return (dest);
	dest1 = dest;
	src1 = src;
	i = 0;
	if (dest1 > src1)
	{
		while (size-- > 0)
			dest1[size] = src1[size];
	}
	else
	{
		while (i < size)
		{
			dest1[i] = src1[i];
			i++;
		}
	}
	return (dest1);
}
