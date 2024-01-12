/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:19:17 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 13:05:24 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbElement, size_t sizeElement)
{	
	void	*res;

	if ((nbElement * sizeElement > 65535)
		|| (nbElement > 65535 && sizeElement > 65535))
		return (0);
	res = malloc(sizeElement * (nbElement));
	if (!res)
		return (NULL);
	ft_bzero(res, nbElement * sizeElement);
	return (res);
}
