/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:35:08 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/18 21:39:01 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int only_n(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_arg(char *str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void ft_echo(t_minishell *cmd)
{
	int		i;
	int		has_n;
	t_args  *arg;
	
	i = 1;
	has_n = 0;
	arg = cmd->args;
	if (!cmd->args->cmd[1])
		return ;
	if ((ft_strncmp(cmd->args->cmd[1], "-n", ft_strlen(cmd->args->cmd[1])) == 0) || only_n(cmd->args->cmd[1] + 1))
	{
		has_n = 1;
		i++;
	}
	// while (arg->cmd[i] && (ft_strncmp(cmd->args->cmd[i], "-n", ft_strlen(cmd->args->cmd[1])) == 0 || only_n(cmd->args->cmd[1] + 1)))
	// 	i++;
	while (arg->cmd[i])
	{
		if ((!has_n && i > 1) || (has_n && i > 2))
			write(1, " ", 1);
		print_arg(arg->cmd[i]);
		i++;
	}
	if (!has_n)
		write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}
