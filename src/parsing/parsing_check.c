/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:04:01 by aleite-b          #+#    #+#             */
/*   Updated: 2024/02/01 10:09:47 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_elem(char *cmd)
{
	char	trigger;
	int		i;

	trigger = '/';
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && trigger == '/')
			trigger = '\'';
		else if (cmd[i] == '\"' && trigger == '/')
			trigger = '\"';
		else if (cmd[i] == trigger && trigger != '/')
			trigger = '/';
		i++;
	}
	if (trigger == '/')
		return (0);
	else
		return (1);
}

int	chev_loop(char *cmd, int *i, char *trigger, char *chevron)
{
	int		count;

	if (cmd[*i] == '\'' && *trigger == '/')
		*trigger = '\'';
	else if (cmd[*i] == '\"' && *trigger == '/')
		*trigger = '\"';
	else if (cmd[*i] == *trigger && *trigger != '/')
		*trigger = '/';
	else if ((cmd[*i] == '>' || cmd[*i] == '<') && (*trigger == '/'))
	{
		count = 0;
		*chevron = cmd[*i];
		while (cmd[*i] && cmd[*i + count] == *chevron)
			count++;
		if (count > 2 || (cmd[*i + count] == '<' && cmd[*i] == '>') || (cmd[*i
					+ count] == '>' && cmd[*i] == '<'))
			return (1);
	}
	return (0);
}

int	check_chev(char *cmd)
{
	int		i;
	char	chevron;
	char	trigger;

	i = 0;
	chevron = '/';
	trigger = '/';
	while (cmd[i])
	{
		if (chev_loop(cmd, &i, &trigger, &chevron))
			return (1);
		i++;
	}
	return (0);
}

int	empty_loop(char *cmd, int i)
{
	int		count;

	count = 1;
	while (cmd[i + count] && is_special_char(cmd[i + count]))
		count++;
	while (cmd[i + count] && is_spaces(cmd[i + count]))
		count++;
	if (is_special_char(cmd[i + count]) || cmd[i + count] == '\0')
		return (1);
	return (0);
}

int	check_empty(char *cmd)
{
	int		i;
	char	trigger;

	trigger = '/';
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && trigger == '/')
			trigger = '\'';
		else if (cmd[i] == '\"' && trigger == '/')
			trigger = '\"';
		else if (cmd[i] == trigger && trigger != '/')
			trigger = '/';
		if (is_special_char(cmd[i]) && trigger == '/')
			if (empty_loop(cmd, i))
				return (1);
		i++;
	}
	return (0);
}
