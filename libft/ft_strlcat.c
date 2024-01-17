/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:56:02 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 15:55:53 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_length;
	size_t	src_length;

	if ((!src || !dest) && size == 0)
		return ((size_t) NULL);
	dest_length = ft_strlen(dest);
	src_length = ft_strlen(src);
	i = 0;
	j = dest_length;
	if (size > 0 && dest_length < size - 1)
	{
		while (src[i] && dest_length + i < (size - 1))
		{
			dest[j] = src[i];
			j++;
			i++;
		}
		dest[j] = '\0';
	}
	if (size <= dest_length)
		return (src_length + size);
	return (dest_length + src_length);
}
