/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:36 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 14:29:14 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(char *)(buffer + i) = 0;
		i++;
	}
}
