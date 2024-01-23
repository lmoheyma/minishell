/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:51:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/23 15:32:28 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trigger(char c, char *trigger)
{
	int	i;

	i = 0;
	if (c == '\'' && *trigger == '/')
	{
		*trigger = '\'';
		i++;
	}
	else if (c == '\"' && *trigger == '/')
	{
		*trigger = '\"';
		i++;
	}
	else if (c == *trigger && *trigger != '/')
	{
		*trigger = '/';
		i++;
	}
	return (i);
}

static int	count_str(char const *s)
{
	int		i;
	int		words;
	char	trigger;

	words = 0;
	i = 0;
	trigger = '/';
	while (s[i])
	{
		if (s[i] == '\'' && trigger == '/')
			trigger = '\'';
		else if (s[i] == '\"' && trigger == '/')
			trigger = '\"';
		else if (s[i] == trigger && trigger != '/')
			trigger = '/';
		if ((s[i + 1] == ' ' || s[i + 1] == '\0') && (s[i] != ' '
				|| s[i] != '\0') && trigger == '/')
			words++;
		i++;
	}
	return (words);
}

static int	get_len(char *s, int add)
{
	int		i;
	int		len;
	char	trigger;

	i = 0;
	len = 0;
	trigger = '/';
	while ((s[i + len] != ' ' && s[i + len]) || (trigger != '/' && s[i + len]))
	{
		if (ft_trigger(s[i + len], &trigger))
			i++;
		else
			len++;
	}
	if (add)
		return (len + i);
	else
		return (len);
}

static char	*write_word(char *s)
{
	int		i;
	int		j;
	char	*str;
	char	trigger;

	i = 0;
	j = 0;
	trigger = '/';
	str = malloc(sizeof(char) * (get_len(s + i, 0) + 1));
	if (!str)
		return (NULL);
	while ((s[i + j] != ' ' && s[i + j]) || (trigger != '/' && s[i + j]))
	{
		if (ft_trigger(s[i + j], &trigger))
			j++;
		else
		{
			str[i] = s[i + j];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_args(char *s)
{
	char	**str;
	int		words;
	int		i;
	int		j;

	words = count_str(s);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i])
	{
		str[j] = write_word(s + i);
		if (!str[j])
		{
			j--;
			while (j--)
				free(str[j]);
			return (NULL);
		}
		j++;
		i += get_len(s + i, 1);
		while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
			i++;
	}
	str[j] = 0;
	return (str);
}
