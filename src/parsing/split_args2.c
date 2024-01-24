/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:51:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/24 16:49:39 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_str(char const *s)
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
