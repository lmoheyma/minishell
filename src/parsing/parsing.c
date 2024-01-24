/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:56:47 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/24 16:58:28 by aleite-b         ###   ########.fr       */
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

int	check_chevrons(char *cmd)
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
			while (cmd[i + count] == chevron)
				count++;
			if (count > 2 || (cmd[i + count] == '<' && cmd[i] == '>') || (cmd[i
						+ count] == '>' && cmd[i] == '<'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	parse_all_minishell(t_minishell *minishell, char *cmd)
{
	if (get_elem(cmd) || get_elem(cmd))
		return (ft_err(minishell, "Guillemets non fermees !\n", 2), 1);
	if (check_chevrons(cmd))
		return (ft_err(minishell, "bash: syntax error near unexpected token\n",
				2), 1);
	if (setup_tokens(minishell, cmd))
		return (1);
	if (setup_args(minishell))
		return (ft_err(minishell, "Arg Malloc err\n", 1), 1);
	minishell->nb_cmd = ft_cmdsize(minishell->args);
	minishell->is_pipe = 0;
	if (minishell->nb_cmd > 1)
		minishell->is_pipe = 1;
	minishell->fd_in = 0;
	minishell->fd_out = 1;
	if (setup_files(minishell))
		return (1);
	return (0);
}
