/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:51:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/25 16:54:45 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	get_len_split(char *s, int add)
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

static char	*write_word_split(char *s)
{
	int		i;
	int		j;
	char	*str;
	char	trigger;

	i = 0;
	j = 0;
	trigger = '/';
	str = malloc(sizeof(char) * (get_len_split(s + i, 0) + 1));
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

static int	ft_split_args2(char **str, char *s, int *i, int *j)
{
	str[*j] = write_word_split(s + *i);
	if (!str[*j])
	{
		*j -= 1;
		while (*j != 0)
		{
			free(str[*j]);
			*j -= 1;
		}
		return (1);
	}
	*j += 1;
	*i += get_len_split(s + *i, 1);
	while (s[*i] == 32 || (s[*i] >= 9 && s[*i] <= 13))
		*i += 1;
	return (0);
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
		if (ft_split_args2(str, s, &i, &j))
			return (NULL);
	}
	str[j] = 0;
	return (str);
}
