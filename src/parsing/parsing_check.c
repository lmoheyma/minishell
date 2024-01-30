/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:04:01 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/30 15:04:17 by aleite-b         ###   ########.fr       */
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

int	check_chev(char *cmd)
{
	int		i;
	int		count;
	char	chevron;

	i = 0;
	count = 0;
	chevron = '/';
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			count = 0;
			chevron = cmd[i];
			while (cmd[i] && cmd[i + count] == chevron)
				count++;
			if (count > 2 || (cmd[i + count] == '<' && cmd[i] == '>') || (cmd[i
						+ count] == '>' && cmd[i] == '<'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_pipe(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			count = 0;
			while (cmd[i] && cmd[i + count] == '|')
				count++;
			if (count > 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_empty(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	while (cmd[i])
	{
		if (is_special_char(cmd[i]))
		{
			count = 1;
			while (cmd[i + count] && is_special_char(cmd[i + count]))
				count++;
			while (cmd[i + count] && is_spaces(cmd[i + count]))
				count++;
			if (is_special_char(cmd[i + count]) || cmd[i + count] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_ng(char *cmd)
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
		else if (cmd[i] == ';' && trigger == '/')
			return (1);
		else if (cmd[i] == '&' && trigger == '/')
			return (1);
		i++;
	}
	return (0);
}
