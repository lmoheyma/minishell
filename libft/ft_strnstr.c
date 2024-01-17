/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:47:50 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 15:19:46 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *str2, size_t size)
{
	size_t	j;
	size_t	i;

	if ((!str || !str2) && size == 0)
		return (NULL);
	i = 0;
	j = 0;
	if (str2[i] == '\0')
		return ((char *)str);
	while (str[i] && i < size)
	{
		j = 0;
		while (str[i + j] == str2[j] && (i + j) < size)
		{
			if (!str2[j + 1])
				return ((char *)str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
