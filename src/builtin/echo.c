/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:35:08 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/22 17:15:14 by lmoheyma         ###   ########.fr       */
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
		if (ft_strncmp(str + i, "\\n", 2) == 0)
		{
			ft_putchar_fd('\n', 1);
			i++;
		}
		else
			ft_putchar_fd(str[i], 1);
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
	{
		ft_putchar_fd('\n', 1);
		exit(EXIT_SUCCESS);
	}
	while (arg->cmd && ((ft_strcmp(arg->cmd[i], "-n") == 0) || (arg->cmd[i][0] == '-' && only_n(arg->cmd[i] + 1))))
	{
		has_n = 1;
		i++;
	}
	if (ft_strncmp(arg->cmd[1], "$?", 2) == 0)
	{
		ft_putnbr_fd(cmd->exit_code, 1);
		if (!has_n)
			write(1, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	while (arg->cmd[i])
	{
		ft_putstr_fd(arg->cmd[i], 1);
		if (arg->cmd[i + 1] && arg->cmd[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (!has_n)
		write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}
