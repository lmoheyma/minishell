/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:13:26 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/08 18:33:36 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(char *buffer, int v, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(unsigned char *)(buffer + i) = (unsigned char)v;
		i++;
	}
	return (buffer);
}

/*
#include <stdio.h>

int main()
{
	printf("%s", (char *)ft_memset("Hello World", 'J', 5));
}*/
