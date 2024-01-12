/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:27:07 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 14:36:13 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str, const char *str2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return ((unsigned char)str[i] -(unsigned char)str2[i]);
		i++;
	}
	if (i < size)
		return ((unsigned char)str[i] - str2[i]);
	return (0);
}
