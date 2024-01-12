/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:26:30 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/13 16:21:45 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_next_word(char **s, char c)
{
	while (**s != c && **s)
		(*s)++;
}

char	*ft_strncopy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	nb_words(char const *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			return (nb_words);
		nb_words++;
		while (s[i] != c && s[i])
			i++;
	}
	return (nb_words);
}

int	word_len(char **s, char c)
{
	int	i;

	i = 0;
	while ((*s)[i] == c && (*s)[i])
		i++;
	*s += i;
	i = 0;
	while ((*s)[i] != c && (*s)[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**res;
	int		nb_word;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	len = 0;
	nb_word = nb_words(s, c);
	res = malloc((nb_word + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (nb_word-- > 0)
	{
		len = word_len(&str, c);
		res[i] = ft_calloc(len + 1, sizeof(char));
		ft_strncopy(res[i], str, len);
		get_next_word(&str, c);
		i++;
	}
	res[i] = NULL;
	return (res);
}
