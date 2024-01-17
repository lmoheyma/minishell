/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:54:02 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 15:25:02 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	char_in_charset(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	i = 0;
	while (s1[i] && char_in_charset(s1[i], set))
		i++;
	while (j > i && char_in_charset(s1[j - 1], set))
		j--;
	res = (char *)malloc(sizeof(*s1) * (j - i + 1));
	if (!res)
		return (NULL);
	k = 0;
	while (i < j)
	{
		res[k] = s1[i];
		i++;
		k++;
	}
	res[k] = '\0';
	return (res);
}
