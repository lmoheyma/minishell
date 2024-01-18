/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:26:28 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/17 14:56:54 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_spaces(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	is_special_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

void	skip_spaces(char *str, int *i)
{
	while (is_spaces(str[*i]))
		*i += 1;
}

int	is_cmd(char *type)
{
	if (ft_strncmp(type, "pipe", 4) == 0
		|| ft_strncmp(type, "simple_cmd", 10) == 0)
		return (1);
	else
		return (0);
}

void	skip_special_char(char *str, int *i)
{
	while (is_special_char(str[*i]))
		*i += 1;
}
