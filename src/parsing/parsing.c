/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:56:47 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/30 15:06:51 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	all_char(char *cmd, char c)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == c)
		i++;
	if (cmd[i])
		return (0);
	else
		return (1);
}

void	init_vars(t_minishell *minishell)
{
	minishell->nb_cmd = ft_cmdsize(minishell->args);
	minishell->is_pipe = 0;
	if (minishell->nb_cmd > 1)
		minishell->is_pipe = 1;
	minishell->fd_in = 0;
	minishell->fd_out = 1;
}

int	parse_all_minishell(t_minishell *minishell, char *cmd)
{
	if (get_elem(cmd) || check_chev(cmd) || check_pipe(cmd) || check_empty(cmd)
		|| check_ng(cmd) || all_char(cmd, '\'') || all_char(cmd, '\"')
		|| ft_strcmp(cmd, "\\") == 0)
	{
		g_exit_code = 2;
		return (ft_putstr_fd("bash: syntax error near unexpected token\n", 2),
			1);
	}
	if (setup_tokens(minishell, cmd))
		return (1);
	if (setup_args(minishell))
		return (ft_err(minishell, "Arg Malloc err\n", 1), 1);
	init_vars(minishell);
	if (setup_files(minishell))
	{
		if (minishell->fd_in != 0 && minishell->fd_in != -1)
			close(minishell->fd_in);
		if (minishell->fd_out != 1 && minishell->fd_out != -1)
			close(minishell->fd_out);
		return (1);
	}
	return (0);
}
