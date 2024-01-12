/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:51:10 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 16:22:46 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{	
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

/*
#include <stdio.h>

int main()
{
	printf("%d\n", atoi(((void *)0)));
	printf("%d", ft_atoi(((void *)0)));

	return (0);
}*/
